// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_DREMEL_ASSEMBLING_H_
#define INCLUDE_IMLAB_DREMEL_ASSEMBLING_H_
//---------------------------------------------------------------------------
#include <vector>
#include "./storage.h"
#include "./field_reader.h"
#include "./record_fsm.h"
#include "./schema_helper.h"
#include <google/protobuf/message.h>
//---------------------------------------------------------------------------
namespace imlab {
namespace dremel {
//---------------------------------------------------------------------------
using namespace google::protobuf;
using TID = uint64_t;

template<class R>
class RecordAssembler {
    static_assert(std::is_base_of<Message, R>::value, "R must be derived from google::protobuf::Message");

 public:
    /// Creates a record assembler; initiated to read the record where the current set of readers point to.
    /// This assembler is stateful:
    /// You can repeatedly call AssembleNextRecord() to assemble the following records from the storage as well.
    /// The Assembler is not thread-safe.
    RecordAssembler(RecordFSM& fsm, std::vector<IFieldReader*>& readers) : _fsm(fsm), _root_reader(readers[0]) {
        _field_reader_map.clear();
        for (auto& r : readers) {
            _field_reader_map[r->field()] = r;
        }
    }

    /// Assembles a shredded record from a column-store table.
    R AssembleNextRecord() {
        R record {};  // Record that is assembled

        // Init all the things for a new record.
        _msg_stack = { &record };
        _last_read_field = nullptr;
        _currently_read_field = _root_reader->field();

        while (_currently_read_field != nullptr) {
            auto value = _field_reader_map.at(_currently_read_field)->ReadNext();
            if (!value.is_null()) {
                MoveToLevel(_currently_read_field);
                value.AppendToRecord(_msg_stack[_msg_stack.size() - 1]);
            } else {
                auto* new_level = _currently_read_field;
                for (int i = 0; i < GetFullDefinitionLevel(_currently_read_field) - value.definition_level(); i++) {
                    new_level = GetFieldDescriptor(new_level->containing_type());
                }
                MoveToLevel(new_level);
            }

            _currently_read_field = _fsm.NextField(_currently_read_field, _field_reader_map.at(_currently_read_field)->Peek().repetition_level());
            ReturnToLevel(_currently_read_field);
        }

        ReturnToLevel(nullptr);
        return record;
    }

 protected:
    // In the original paper, the following two FieldDescriptors are actually FieldReaders.
    // But it doesn't really matter and I found it easier to work with FieldDescriptors here.
    const FieldDescriptor* _last_read_field = nullptr;
    const FieldDescriptor* _currently_read_field = nullptr;
    // This stack resembles the nested structure of a message.
    std::vector<Message*> _msg_stack {};

    // A finite state machine to switch between fields within a record.
    RecordFSM& _fsm;
    // A reader to the first field in the record.
    IFieldReader* _root_reader;
    // We also create a mapping between fields and FieldReaders
    std::unordered_map<const FieldDescriptor*, IFieldReader*> _field_reader_map;


    void MoveToLevel(const FieldDescriptor* new_field) {
        // Unwind message stack: End nested records up to the level of the lowest common ancestor.
        const auto* common_ancestor = GetCommonAncestor(_last_read_field, _currently_read_field);
        auto common_ancestor_level = GetFullDefinitionLevel(common_ancestor);
        int elements_to_remove = _msg_stack.size() - common_ancestor_level - 1/*don't pop root*/;
        if (elements_to_remove > 0) {
            for (int i = 0; i < elements_to_remove; i++) {
                _msg_stack.pop_back();
            }
            assert(GetFieldDescriptor(_msg_stack[_msg_stack.size() - 1]->GetDescriptor()) == common_ancestor);
        }

        // --------------------------------------------------------------------
        // Re-build message stack accordingly: Start nested records from the level of the lowest common ancestor.

        // The target_field_type is "where we want to end up".
        const Descriptor* target_field_type;
        if (new_field == nullptr) {
            // If a field does not exist in a record, new_field might be the message root.
            target_field_type = _msg_stack[0]->GetDescriptor();
        } else if (new_field->type() == FieldDescriptor::TYPE_GROUP || new_field->type() == FieldDescriptor::TYPE_MESSAGE) {
            // An inner node is just a normal case.
            target_field_type = new_field->message_type();
        } else {
            // If we are at a leaf field, we actually want the containing field because of how Protobuf handles the fields.
            target_field_type = new_field->containing_type();
        }

        // Maybe the target_field_type is even further up...
        // Unwind the message stack even further if that's the case.
        if (GetFullDefinitionLevel(GetFieldDescriptor(target_field_type)) < _msg_stack.size() - 1) {
            ReturnToLevel(GetFieldDescriptor(target_field_type));
        }

        // Now we can actually start to build up the message stack again up to target_field_type.
        // First, gather which fields we need to add to our stack (reverse order), then convert them to messages.
        std::vector<const FieldDescriptor*> parents {};
        while (target_field_type != _msg_stack[_msg_stack.size() - 1]->GetDescriptor()) {
            parents.push_back(GetFieldDescriptor(target_field_type));
            target_field_type = GetFieldDescriptor(target_field_type)->containing_type();
        }
        for (auto field = parents.rbegin(); field != parents.rend(); field++) {
            Message* parent_msg = _msg_stack[_msg_stack.size() - 1];
            Message* child_msg = ((*field)->is_repeated())? parent_msg->GetReflection()->AddMessage(parent_msg, *field)
                                                          : parent_msg->GetReflection()->MutableMessage(parent_msg, *field);
            _msg_stack.push_back(child_msg);
        }

        _last_read_field = new_field;
    }

    void ReturnToLevel(const FieldDescriptor* new_field) {
        // Unwind message stack: End nested records up to the level of the lowest common ancestor.
        const auto* common_ancestor = GetCommonAncestor(_last_read_field, new_field);
        auto common_ancestor_level = GetFullDefinitionLevel(common_ancestor);
        int elements_to_remove = _msg_stack.size() - common_ancestor_level - 1/*don't pop root*/;
        if (elements_to_remove >= 0) {
            for (int i = 0; i < elements_to_remove; i++) {
                _msg_stack.pop_back();
            }
            assert(GetFieldDescriptor(_msg_stack[_msg_stack.size() - 1]->GetDescriptor()) == common_ancestor);
            _last_read_field = common_ancestor;
        }
    }
};

//---------------------------------------------------------------------------
}  // namespace dremel
}  // namespace imlab
//---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_DREMEL_ASSEMBLING_H_
//---------------------------------------------------------------------------
