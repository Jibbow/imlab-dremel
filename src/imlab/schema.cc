// ---------------------------------------------------------------------------
// This file is auto-generated.
// Do not edit this file directly.
// ---------------------------------------------------------------------------
#include "imlab/schema.h"
// ---------------------------------------------------------------------------
namespace imlab {
namespace schema {
// ---------------------------------------------------------------------------

const std::vector<IU> DocumentTable::IUs = {
    IU("Document", "DocId", schemac::Type::Integer()),
    IU("Document", "Links.Backward", schemac::Type::Integer()),
    IU("Document", "Links.Forward", schemac::Type::Integer()),
    IU("Document", "Name.Url", schemac::Type::Varchar(30)),
    IU("Document", "Name.Language.Code", schemac::Type::Varchar(30)),
    IU("Document", "Name.Language.Country", schemac::Type::Varchar(30)),
};

std::vector<const IU*> DocumentTable::get_ius() {
    std::vector<const IU*> refs {};
    refs.reserve(IUs.size());
    for (auto& iu : IUs) {
        refs.push_back(&iu);
    }
    return refs;
}

uint64_t DocumentTable::insert(Document record) {

}

// ---------------------------------------------------------------------------
}  // namespace schema
}  // namespace imlab
// ---------------------------------------------------------------------------
