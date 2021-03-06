// ---------------------------------------------------------------------------
// This file is auto-generated.
// Do not edit this file directly.
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_SCHEMA_H_
#define INCLUDE_IMLAB_SCHEMA_H_
// ---------------------------------------------------------------------------
#include <optional>
#include <vector>
#include "./schema.pb.h"
#include "../../../include/imlab/dremel/storage.h"
#include "../../../include/imlab/dremel/field_writer.h"
#include "../../../include/imlab/infra/types.h"
#include <google/protobuf/descriptor.h>
// ---------------------------------------------------------------------------
namespace imlab {
namespace schema {
// ---------------------------------------------------------------------------
using namespace dremel;

class DocumentTable : public TableBase {
 public:
    /// Insert a new record into the table.
    uint64_t insert(Document& record);
    /// Gets one record from the table.
    Document get(uint64_t tid, const std::vector<const FieldDescriptor*>& fields) { return get_range(tid, tid + 1, fields)[0]; }
    /// Gets a range of record from the table. `to_tid` is exclusive.
    std::vector<Document> get_range(uint64_t from_tid, uint64_t to_tid, const std::vector<const FieldDescriptor*>& fields);
    /// Get the corresponding FieldWriter-tree for this table.
    FieldWriter* record_writer() override { return &Root_Writer; }
    /// Get a reference to the fields in this table.
    static std::vector<const FieldDescriptor*> fields();

 protected:
    static inline const FieldDescriptor* DocId_Descriptor = Document::descriptor()->FindFieldByName("DocId");
    DremelColumn<int64_t> DocId_Column { DocId_Descriptor };
    std::vector<uint64_t> DocId_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    static inline const FieldDescriptor* Links_Backward_Descriptor = Document_Links::descriptor()->FindFieldByName("Backward");
    DremelColumn<int64_t> Links_Backward_Column { Links_Backward_Descriptor };
    std::vector<uint64_t> Links_Backward_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    static inline const FieldDescriptor* Links_Forward_Descriptor = Document_Links::descriptor()->FindFieldByName("Forward");
    DremelColumn<int64_t> Links_Forward_Column { Links_Forward_Descriptor };
    std::vector<uint64_t> Links_Forward_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    static inline const FieldDescriptor* Name_Language_Code_Descriptor = Document_Name_Language::descriptor()->FindFieldByName("Code");
    DremelColumn<std::string> Name_Language_Code_Column { Name_Language_Code_Descriptor };
    std::vector<uint64_t> Name_Language_Code_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    static inline const FieldDescriptor* Name_Language_Country_Descriptor = Document_Name_Language::descriptor()->FindFieldByName("Country");
    DremelColumn<std::string> Name_Language_Country_Column { Name_Language_Country_Descriptor };
    std::vector<uint64_t> Name_Language_Country_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    static inline const FieldDescriptor* Name_Url_Descriptor = Document_Name::descriptor()->FindFieldByName("Url");
    DremelColumn<std::string> Name_Url_Column { Name_Url_Descriptor };
    std::vector<uint64_t> Name_Url_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    // A tree-like structure of FieldWriters
    AtomicFieldWriter<int64_t> DocId_Writer { &DocId_Column };
    AtomicFieldWriter<int64_t> Links_Backward_Writer { &Links_Backward_Column };
    AtomicFieldWriter<int64_t> Links_Forward_Writer { &Links_Forward_Column };
    AtomicFieldWriter<std::string> Name_Language_Code_Writer { &Name_Language_Code_Column };
    AtomicFieldWriter<std::string> Name_Language_Country_Writer { &Name_Language_Country_Column };
    AtomicFieldWriter<std::string> Name_Url_Writer { &Name_Url_Column };
    ComplexFieldWriter Root_Writer { nullptr, { &DocId_Writer, &Links_Writer, &Name_Writer } };
    ComplexFieldWriter Links_Writer { Document::descriptor()->FindFieldByName("links"), { &Links_Backward_Writer, &Links_Forward_Writer } };
    ComplexFieldWriter Name_Writer { Document::descriptor()->FindFieldByName("name"), { &Name_Language_Writer, &Name_Url_Writer } };
    ComplexFieldWriter Name_Language_Writer { Document_Name::descriptor()->FindFieldByName("language"), { &Name_Language_Code_Writer, &Name_Language_Country_Writer } };
};

// ---------------------------------------------------------------------------
}  // namespace schema
}  // namespace imlab
// ---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_SCHEMA_H_
// ---------------------------------------------------------------------------
