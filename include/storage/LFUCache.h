#ifndef GUARD_C3D3A3CF_8C5E_49DF_8245_E0387D3F4723
#define GUARD_C3D3A3CF_8C5E_49DF_8245_E0387D3F4723

#include <cstdint>
#include <list>
#include <queue>
#include <shared_mutex>
#include <unordered_map>

#include "IStorage.h"
#include "StorageTypes.h"

namespace storage {

class LFUCache : public IStorage {
public:
  LFUCache(IStorage &storage, uint32_t capacity)
      : _storage(storage), _capacity(capacity) {}

  ReadResult readByIndex(Index index) override;

  void writeByIndex(Index index, const Value &val) override;

private:
  using Cache = std::unordered_map<Index, Value>;

  void updateLFU(Index index);
  void updateFreqHistory(Index index);
  void cache(Index index, const Value &val);
  Cache::iterator findLFU();

  IStorage &_storage;
  uint32_t _capacity;
  Cache _cache;
  std::unordered_map<Index, uint64_t> _freq_history;
  mutable std::shared_timed_mutex _mutex;
};
} // namespace storage

#endif /* GUARD_C3D3A3CF_8C5E_49DF_8245_E0387D3F4723 */
