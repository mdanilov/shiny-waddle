#ifndef GUARD_C88672CE_CD8B_49AC_BC5D_7A08C1B3C75F
#define GUARD_C88672CE_CD8B_49AC_BC5D_7A08C1B3C75F

#include <gmock/gmock.h>

#include "storage/IStorage.h"

namespace storage {
class StorageMock : public IStorage {
public:
  MOCK_METHOD1(readByIndex, ReadResult(Index index));
  MOCK_METHOD2(writeByIndex, void(Index index, const Value &val));
};
} // namespace storage

#endif /* GUARD_C88672CE_CD8B_49AC_BC5D_7A08C1B3C75F */
