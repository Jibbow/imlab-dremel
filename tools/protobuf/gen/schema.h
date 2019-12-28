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
#include "imlab/dremel/storage.h"
#include "imlab/dremel/field_writer.h"
#include "imlab/infra/types.h"
#include "imlab/algebra/iu.h"
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
    FieldWriter* get_record_writer() override { return &Root_Writer; }
    /// Get a reference to the IUs in this table.
    static std::vector<const IU*> get_ius();

 protected:
    DremelColumn<Integer> DocId { Document::descriptor()->FindFieldByName("DocId") };
    std::vector<uint64_t> DocId_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    DremelColumn<Integer> Links_Backward { Document_Links::descriptor()->FindFieldByName("Backward") };
    std::vector<uint64_t> Links_Backward_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    DremelColumn<Integer> Links_Forward { Document_Links::descriptor()->FindFieldByName("Forward") };
    std::vector<uint64_t> Links_Forward_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    DremelColumn<Varchar<30>> Name_Language_Code { Document_Name_Language::descriptor()->FindFieldByName("Code") };
    std::vector<uint64_t> Name_Language_Code_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    DremelColumn<Varchar<30>> Name_Language_Country { Document_Name_Language::descriptor()->FindFieldByName("Country") };
    std::vector<uint64_t> Name_Language_Country_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    DremelColumn<Varchar<30>> Name_Url { Document_Name::descriptor()->FindFieldByName("Url") };
    std::vector<uint64_t> Name_Url_Record_TIDs;  // Maps the beginning of a record to a TID in the column.

    // A tree-like structure of FieldWriters
    AtomicFieldWriter<Integer> DocId_Writer { &DocId };
    AtomicFieldWriter<Integer> Links_Backward_Writer { &Links_Backward };
    AtomicFieldWriter<Integer> Links_Forward_Writer { &Links_Forward };
    AtomicFieldWriter<Varchar<30>> Name_Language_Code_Writer { &Name_Language_Code };
    AtomicFieldWriter<Varchar<30>> Name_Language_Country_Writer { &Name_Language_Country };
    AtomicFieldWriter<Varchar<30>> Name_Url_Writer { &Name_Url };
    ComplexFieldWriter Root_Writer { nullptr, { &DocId_Writer, &Links_Writer, &Name_Writer } };
    ComplexFieldWriter Links_Writer { Document::descriptor()->FindFieldByName("links"), { &Links_Backward_Writer, &Links_Forward_Writer } };
    ComplexFieldWriter Name_Writer { Document::descriptor()->FindFieldByName("name"), { &Name_Language_Writer, &Name_Url_Writer } };
    ComplexFieldWriter Name_Language_Writer { Document_Name::descriptor()->FindFieldByName("language"), { &Name_Language_Code_Writer, &Name_Language_Country_Writer } };

    static const std::vector<IU> IUs;
};

// ---------------------------------------------------------------------------
}  // namespace schema
}  // namespace imlab
// ---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_SCHEMA_H_
// ---------------------------------------------------------------------------
