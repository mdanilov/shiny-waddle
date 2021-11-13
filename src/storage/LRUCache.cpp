#include "storage/LRUCache.h"

#include <algorithm>
#include <cstdint>
#include <list>
#include <shared_mutex>
#include <unordered_map>

namespace storage {
void LRUCache::updateLRU(Index index) {
  auto it = std::find(_lru.begin(), _lru.end(), index);
  if (it != _lru.end()) {
    _lru.splice(_lru.begin(), _lru, it);
  }
}

void LRUCache::cache(Index index, const Value &val) {
  if (_cache.size() >= _cache_size) {
    // remove LRU from the cache
    Index index_to_remove = _lru.back();
    _lru.pop_back();
    _cache.erase(index_to_remove);
  }

  _cache[index] = val;
  _lru.push_front(index);
}

ReadResult LRUCache::readByIndex(Index index) {
  {
    std::shared_lock<std::shared_timed_mutex> lock(_mutex);

    auto it = _cache.find(index);
    if (it != _cache.end()) {
      // cache hit
      updateLRU(index);
      return {it->second, false};
    }
  }

  // cache miss
  Value val = _storage.readByIndex(index).value;

  {
    std::shared_lock<std::shared_timed_mutex> lock(_mutex);
    cache(index, val);
  }

  return {val, true};
}

void LRUCache::writeByIndex(Index index, const Value &val) {
  {
    std::unique_lock<std::shared_timed_mutex> lock(_mutex);

    auto it = _cache.find(index);
    if (it != _cache.end()) {
      // cache hit, update the value in cache
      updateLRU(index);
      _cache[index] = val;
    } else {
      cache(index, val);
    }
  }

  _storage.writeByIndex(index, val);
}
} // namespace storage
