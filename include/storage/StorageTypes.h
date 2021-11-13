#ifndef GUARD_BDF770A9_0F21_4F1E_8D9A_D60F0018954B
#define GUARD_BDF770A9_0F21_4F1E_8D9A_D60F0018954B

#include <cstdint>
#include <string>

namespace storage {

using Index = uint32_t;
using Value = std::string;

struct ReadResult {
  Value value;
  bool cache_miss;

  ReadResult(const Value &val, bool cache_miss = true)
      : value(val), cache_miss(cache_miss) {}
};
} // namespace storage

#endif /* GUARD_BDF770A9_0F21_4F1E_8D9A_D60F0018954B */
