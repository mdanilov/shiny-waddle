#ifndef GUARD_EB85089B_FF9D_480A_B150_47E593590B05
#define GUARD_EB85089B_FF9D_480A_B150_47E593590B05

#include "IStorage.h"
#include "StorageTypes.h"

#include <shared_mutex>
#include <string>

namespace storage {
/**
 * \brief Implements IStorage interface for the text file.
 * Where each line in the file contains the value. And the key is the line
 * number. The first line has key 1, second is 2, etc.
 *
 * No caching. Thread-safe implementation.
 *
 */

class FileStorage : public IStorage {
public:
  /**
   * \brief Construct a new File Storage object
   *
   * @param file path to the database text file
   */
  explicit FileStorage(const std::string &file) : _file(file) {}

  /**
   * \brief Read the value from the line specified by index
   *
   * @param index line in the file
   * @return ReadResult read result. Always returns cache miss.
   */
  ReadResult readByIndex(Index index) override;

  /**
   * \brief Writes new content to the line specified by the index.
   * Note: it requires to overwrite the whole file.
   *
   * First the temporary file with new content is created and then it replaces
   * the current one.
   *
   * @param index of line in the file
   * @param val new line content
   */
  void writeByIndex(Index index, const Value &val) override;

private:
  std::string _file;
  mutable std::shared_timed_mutex _mutex;
};
} // namespace storage

#endif /* GUARD_EB85089B_FF9D_480A_B150_47E593590B05 */
