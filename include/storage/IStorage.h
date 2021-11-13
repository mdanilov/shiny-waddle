#ifndef GUARD_EFBE252D_18BB_49EA_A6A6_D4CF342AD1B7
#define GUARD_EFBE252D_18BB_49EA_A6A6_D4CF342AD1B7

#include "StorageTypes.h"

namespace storage {

class IStorage {
public:
  virtual ReadResult readByIndex(Index index) = 0;
  virtual void writeByIndex(Index index, const Value &val) = 0;
};

} // namespace storage

#endif /* GUARD_EFBE252D_18BB_49EA_A6A6_D4CF342AD1B7 */
