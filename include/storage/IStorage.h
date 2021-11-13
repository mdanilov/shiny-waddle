#ifndef GUARD_EFBE252D_18BB_49EA_A6A6_D4CF342AD1B7
#define GUARD_EFBE252D_18BB_49EA_A6A6_D4CF342AD1B7

#include "StorageTypes.h"

namespace storage {
/**
 * \brief Key/value storage interface. Allows read and write to the storage by
 * key.
 *
 */
class IStorage {
public:
  /**
   * \brief Read the value by index.
   *
   * @param index key
   * @return ReadResult result of the read
   */
  virtual ReadResult readByIndex(Index index) = 0;

  /**
   * \brief Write the value by index.
   *
   * @param index key
   * @param val new value
   */
  virtual void writeByIndex(Index index, const Value &val) = 0;
};

} // namespace storage

#endif /* GUARD_EFBE252D_18BB_49EA_A6A6_D4CF342AD1B7 */
