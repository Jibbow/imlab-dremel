// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#ifndef INCLUDE_IMLAB_DREMEL_FIELD_READER_H_
#define INCLUDE_IMLAB_DREMEL_FIELD_READER_H_
//---------------------------------------------------------------------------
#include "./storage.h"
//---------------------------------------------------------------------------
namespace imlab {
namespace dremel {
//---------------------------------------------------------------------------

class FieldReader {
 public:
    FieldValue ReadNext();
    const FieldDescriptor* field();
};

//---------------------------------------------------------------------------
}  // namespace dremel
}  // namespace imlab
//---------------------------------------------------------------------------
#endif  // INCLUDE_IMLAB_DREMEL_FIELD_READER_H_
//---------------------------------------------------------------------------
