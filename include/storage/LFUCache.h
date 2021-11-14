#ifndef GUARD_C3D3A3CF_8C5E_49DF_8245_E0387D3F4723
#define GUARD_C3D3A3CF_8C5E_49DF_8245_E0387D3F4723

#include <cstdint>
#include <list>
#include <mutex>
#include <queue>
#include <unordered_map>

#include "IStorage.h"
#include "StorageTypes.h"
#include "util/HashMinHeap.h"

namespace storage {
/**
 * \brief Adds LFU cache to the storage.
 *
 * Implements Least Frequently Used (LFU) algorithm.
 *
 * Thread-safe implementation.
 *
 */
class LFUCache : public IStorage {
public:
  /**
   * \brief Construct a new LFUCache object
   *
   * @param storage reference to storage the access to which will be cached.
   * @param cache_size the max cache capacity
   */
  LFUCache(IStorage &storage, uint32_t capacity)
      : _storage(storage), _cache(capacity) {}

  /**
   * \brief Read from underlying storage in case of cache miss. Otherwise take
   * value form the cache.
   *
   * Increment the frequency counter of accessed element if it's already cached.
   *
   * In case of cache miss updates the cache with new element. The LFU element
   * is removed from the cache.
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
  struct CacheEntry {
    uint64_t freq;
    Value value;

    bool operator>(const CacheEntry &e) const { return freq > e.freq; }
    bool operator<(const CacheEntry &e) const { return freq < e.freq; }
  };

  using LFUMinHeap = util::HashMinHeap<Index, CacheEntry>;

  IStorage &_storage;
  LFUMinHeap _cache;
  mutable std::mutex _mutex;
};
} // namespace storage

#endif /* GUARD_C3D3A3CF_8C5E_49DF_8245_E0387D3F4723 */
