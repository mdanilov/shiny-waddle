#include "storage/LFUCache.h"

#include <algorithm>
#include <cstdint>
#include <limits>
#include <list>
#include <shared_mutex>
#include <unordered_map>

namespace storage {
ReadResult LFUCache::readByIndex(Index index) {
  {
    std::lock_guard<std::mutex> lock(_mutex);

    if (_cache.hasKey(index)) {
      CacheEntry entry = _cache.get(index);
      entry.freq++;
      _cache.change(index, entry);
      return {entry.value, false};
    }
  }

  // cache miss
  Value val = _storage.readByIndex(index).value;

  {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_cache.isFull()) {
      _cache.extractMin();
    }
    _cache.insert(index, {1, val});
  }

  return {val, true};
}

void LFUCache::writeByIndex(Index index, const Value &val) {
  {
    std::lock_guard<std::mutex> lock(_mutex);

    if (_cache.hasKey(index)) {
      // update the value in cache
      CacheEntry entry = _cache.get(index);
      entry.value = val;
      _cache.change(index, entry);
    }
  }

  _storage.writeByIndex(index, val);
}
} // namespace storage
