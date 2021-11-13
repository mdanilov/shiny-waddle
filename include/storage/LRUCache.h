#ifndef GUARD_A5DE196B_565A_41DE_8850_9C786861A85D
#define GUARD_A5DE196B_565A_41DE_8850_9C786861A85D

#include <cstdint>
#include <list>
#include <shared_mutex>
#include <unordered_map>

#include "IStorage.h"
#include "StorageTypes.h"

namespace storage {
/**
 * \brief Adds LRU cache to the storage.
 *
 * Implements Least Recently Used (LRU) algorithm.
 *
 * Thread-safe implementation.
 *
 */

class LRUCache : public IStorage {
public:
  /**
   * \brief Construct a new LRUCache object
   *
   * @param storage reference to storage the access to which will be cached.
   * @param cache_size the max cache capacity
   */
  LRUCache(IStorage &storage, uint32_t cache_size)
      : _storage(storage), _cache_size(cache_size) {}

  /**
   * \brief Read from underlying storage in case of cache miss. Otherwise take
   * value form the cache.
   *
   * @param index read key
   * @return ReadResult contains the true cache miss information.
   */
  ReadResult readByIndex(Index index) override;

  /**
   * \brief Writes new value. Updates value in cache if exists.
   * It always writes to the underlying storage.
   *
   * @param index write key
   * @param val new value
   */
  void writeByIndex(Index index, const Value &val) override;

private:
  void updateLRU(Index index);
  void cache(Index index, const Value &val);

  IStorage &_storage;
  uint32_t _cache_size;
  std::unordered_map<Index, Value> _cache;
  std::list<Index> _lru; // store LRU at the front
  mutable std::shared_timed_mutex _mutex;
};
} // namespace storage

#endif /* GUARD_A5DE196B_565A_41DE_8850_9C786861A85D */
