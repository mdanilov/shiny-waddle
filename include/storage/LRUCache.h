#ifndef GUARD_A5DE196B_565A_41DE_8850_9C786861A85D
#define GUARD_A5DE196B_565A_41DE_8850_9C786861A85D

#include <cstdint>
#include <list>
#include <shared_mutex>
#include <unordered_map>

#include "IStorage.h"
#include "StorageTypes.h"

namespace storage {

class LRUCache : public IStorage {
public:
  LRUCache(IStorage &storage, uint32_t cache_size)
      : _storage(storage), _cache_size(cache_size) {}

  ReadResult readByIndex(Index index) override;

  void writeByIndex(Index index, const Value &val) override;

private:
  void updateLRU(Index index);

  IStorage &_storage;
  uint32_t _cache_size;
  std::unordered_map<Index, Value> _cache;
  std::list<Index> _lru; // store LRU at the front
  mutable std::shared_timed_mutex _mutex;
};
} // namespace storage

#endif /* GUARD_A5DE196B_565A_41DE_8850_9C786861A85D */
