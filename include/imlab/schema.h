// ---------------------------------------------------------------------------
// This file is auto-generated.
// Do not edit this file directly.
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_SCHEMA_H_
#define INCLUDE_IMLAB_SCHEMA_H_
// ---------------------------------------------------------------------------
#include "imlab/infra/dremel.h"
#include "imlab/infra/types.h"
#include "imlab/algebra/iu.h"
#include <vector>
#include <optional>
// ---------------------------------------------------------------------------
namespace imlab {
namespace schema {
// ---------------------------------------------------------------------------

struct Document {
    struct Links {
        std::vector<Integer> Backward;
        std::vector<Integer> Forward;
    };
    struct Name {
        struct Language {
            Varchar<30> Code;
            std::optional<Varchar<30>> Country;
        };
        std::vector<Language> language;
        std::optional<Varchar<30>> Url;
    };
    Integer DocId;
    std::optional<Links> links;
    std::vector<Name> name;
};

class DocumentTable : public TableBase {
 public:
    uint64_t insert(Document record);
    static std::vector<const IU*> get_ius();

 private:
    DremelColumn<Integer> DocId {"DocId"};
    std::vector<uint64_t> DocId_Record_TIDs; //  Maps the beginning of a record to a TID in the column.

    DremelColumn<Integer> Links_Backward {"Links.Backward"};
    std::vector<uint64_t> Links_Backward_Record_TIDs; //  Maps the beginning of a record to a TID in the column.

    DremelColumn<Integer> Links_Forward {"Links.Forward"};
    std::vector<uint64_t> Links_Forward_Record_TIDs; //  Maps the beginning of a record to a TID in the column.

    DremelColumn<Varchar<30>> Name_Url {"Name.Url"};
    std::vector<uint64_t> Name_Url_Record_TIDs; //  Maps the beginning of a record to a TID in the column.

    DremelColumn<Varchar<30>> Name_Language_Code {"Name.Language.Code"};
    std::vector<uint64_t> Name_Language_Code_Record_TIDs; //  Maps the beginning of a record to a TID in the column.

    DremelColumn<Varchar<30>> Name_Language_Country {"Name.Language.Country"};
    std::vector<uint64_t> Name_Language_Country_Record_TIDs; //  Maps the beginning of a record to a TID in the column.

    static const std::vector<IU> IUs;
};

// ---------------------------------------------------------------------------
}  // namespace schema
}  // namespace imlab
// ---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_SCHEMA_H_
// ---------------------------------------------------------------------------
