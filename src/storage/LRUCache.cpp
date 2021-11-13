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

ReadResult LRUCache::readByIndex(Index index) {
  {
    std::shared_lock<std::shared_timed_mutex> lock(_mutex);

    auto it = _cache.find(index);
    updateLRU(index);
    if (it != _cache.end()) {
      // cache hit
      return {it->second, false};
    }
  }

  // cache miss
  Value val = _storage.readByIndex(index).value;

  {
    std::shared_lock<std::shared_timed_mutex> lock(_mutex);
    if (_cache.size() >= _cache_size) {
      // remove LRU from the cache
      Index index_to_remove = _lru.back();
      _lru.pop_back();
      _cache.erase(index_to_remove);
    }

    _cache[index] = val;
    _lru.push_front(index);
  }

  return {val, true};
}

void LRUCache::writeByIndex(Index index, const Value &val) {
  {
    std::unique_lock<std::shared_timed_mutex> lock(_mutex);

    // update cache first
    auto it = _cache.find(index);
    if (it != _cache.end()) {
      it->second = val;
    }
  }

  _storage.writeByIndex(index, val);
}
}
