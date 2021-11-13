#ifndef GUARD_EB85089B_FF9D_480A_B150_47E593590B05
#define GUARD_EB85089B_FF9D_480A_B150_47E593590B05

#include "StorageTypes.h"
#include "IStorage.h"

#include <shared_mutex>
#include <string>

namespace storage {

class FileStorage : public IStorage {
public:
  explicit FileStorage(const std::string &file) : _file(file) {}

  ReadResult readByIndex(Index index) override;

  void writeByIndex(Index index, const Value &val) override;

private:
  std::string _file;
  mutable std::shared_timed_mutex _mutex;
};
} // namespace storage

#endif /* GUARD_EB85089B_FF9D_480A_B150_47E593590B05 */
