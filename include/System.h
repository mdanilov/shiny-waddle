#ifndef GUARD_D3422719_5A20_4D8B_A50A_B9DB034B2878
#define GUARD_D3422719_5A20_4D8B_A50A_B9DB034B2878

#include "Runner.h"
#include "reader/CommandReader.h"
#include "reader/Reader.h"
#include "storage/FileStorage.h"
#include "storage/IStorage.h"
#include "storage/LFUCache.h"
#include "writer/CommandReader.h"
#include "writer/Writer.h"

#include <memory>
#include <vector>

namespace executor {

/**
 * \brief Application main facade. Creates and own all objects required to run
 * the program.
 *
 */
class System {
public:
  /**
   * \brief Construct a new System object. Reads the readers and writers
   * configurations and constructs the objects accordingly.
   *
   * @throws std::exception if the configuration is invalid or cannot be read
   *
   * @param cache_size max cache capacity
   * @param readers_config path to the readers config
   * @param writers_config path to the writers config
   * @param items_file path to the database file
   */
  System(uint32_t cache_size, const std::string &readers_config,
         const std::string &writers_config, const std::string &items_file);

  /**
   * \brief Starts the program execution. Invoke all writer/reader runnables and
   * wait until the end of the execution.
   *
   */
  void exec();

private:
  std::vector<std::shared_ptr<reader::CommandReader>> _r_command_readers;
  std::vector<std::shared_ptr<reader::Reader>> _readers;

  std::vector<std::shared_ptr<writer::CommandReader>> _w_command_readers;
  std::vector<std::shared_ptr<writer::Writer>> _writers;

  storage::FileStorage _file_storage;
  storage::LFUCache _cache;

  Runner _runner;
};
} // namespace executor

#endif /* GUARD_D3422719_5A20_4D8B_A50A_B9DB034B2878 */
