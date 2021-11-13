#ifndef GUARD_D3422719_5A20_4D8B_A50A_B9DB034B2878
#define GUARD_D3422719_5A20_4D8B_A50A_B9DB034B2878

#include "Runner.h"
#include "reader/Reader.h"
#include "reader/CommandReader.h"
#include "storage/FileStorage.h"
#include "storage/IStorage.h"
#include "storage/StorageWithLRUCache.h"
#include "writer/Writer.h"
#include "writer/CommandReader.h"

#include <memory>
#include <vector>

namespace executor {

class System {
public:
  System(uint32_t cache_size, const std::string &readers_config,
         const std::string &writers_config, const std::string &items_file);

  void exec();

private:
  std::vector<reader::CommandReader> _rCommandReaders;
  std::vector<std::shared_ptr<reader::Reader>> _readers;

  std::vector<writer::CommandReader> _wCommandReaders;
  std::vector<std::shared_ptr<writer::Writer>> _writers;

  storage::FileStorage _file_storage;
  storage::StorageWithLRUCache _cache;

  Runner _runner;
};
} // namespace executor

#endif /* GUARD_D3422719_5A20_4D8B_A50A_B9DB034B2878 */