#include "storage/LRUCache.h"

#include <algorithm>
#include <cstdint>
#include <list>
#include <shared_mutex>
#include <unordered_map>

namespace storage {
void LRUCache::updateLRU(Index index, const Value &val) {
  _lru.erase(_cache[index]);

  _lru.push_front({index, val});
  _cache[index] = _lru.begin();
}

void LRUCache::cache(Index index, const Value &val) {
  if (isFull()) {
    // remove LRU from the cache
    Index last = _lru.back().first;
    _lru.pop_back();
    _cache.erase(last);
  }

  _lru.push_front({index, val});
  _cache[index] = _lru.begin();
}

ReadResult LRUCache::readByIndex(Index index) {
  {
    std::unique_lock<std::shared_timed_mutex> lock(_mutex);

    auto it = _cache.find(index);
    if (it != _cache.end()) {
      // cache hit
      Value val = _cache[index]->second;
      updateLRU(index, val);
      return {val, false};
    }
  }

  // cache miss
  Value val = _storage.readByIndex(index).value;

  {
    std::unique_lock<std::shared_timed_mutex> lock(_mutex);
    cache(index, val);
  }

  return {val, true};
}

void LRUCache::writeByIndex(Index index, const Value &val) {
  {
    std::unique_lock<std::shared_timed_mutex> lock(_mutex);

    auto it = _cache.find(index);
    if (it != _cache.end()) {
      // update the value in cache
      updateLRU(index, val);
    }
  }

  _storage.writeByIndex(index, val);
}
} // namespace storage
