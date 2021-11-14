#include "storage/LFUCache.h"

#include <algorithm>
#include <cstdint>
#include <limits>
#include <list>
#include <shared_mutex>
#include <unordered_map>

namespace storage {
LFUCache::Cache::iterator LFUCache::findLFU() {
  uint64_t min_frequency = std::numeric_limits<uint64_t>::max();
  Cache::iterator res = _cache.begin();
  for (auto it = _cache.begin(); it != _cache.end(); ++it) {
    uint64_t freq = _freq_history[it->first];
    if (freq < min_frequency) {
      min_frequency = freq;
      res = it;
    }
  }
  return res;
}

void LFUCache::cache(Index index, const Value &val) {
  if (isFull()) {
    auto it = findLFU();
    if (_freq_history[it->first] < _freq_history[index]) {
      // remove LFU from the cache if the new element has higher frequency
      _cache.erase(it);
      _cache[index] = val;
    }
  } else {
    _cache[index] = val;
  }
}

void LFUCache::updateFreqHistory(Index index) {
  auto it = _freq_history.find(index);
  if (it != _freq_history.end()) {
    it->second += 1;
  } else {
    _freq_history[index] = 1;
  }
}

ReadResult LFUCache::readByIndex(Index index) {
  {
    std::lock_guard<std::mutex> lock(_mutex);

    updateFreqHistory(index);

    auto it = _cache.find(index);
    if (it != _cache.end()) {
      // cache hit
      return {it->second, false};
    }
  }

  // cache miss
  Value val = _storage.readByIndex(index).value;

  {
    std::lock_guard<std::mutex> lock(_mutex);
    cache(index, val);
  }

  return {val, true};
}

void LFUCache::writeByIndex(Index index, const Value &val) {
  {
    std::lock_guard<std::mutex> lock(_mutex);

    auto it = _cache.find(index);
    if (it != _cache.end()) {
      // update the value in cache
      _cache[index] = val;
    }
  }

  _storage.writeByIndex(index, val);
}
} // namespace storage
