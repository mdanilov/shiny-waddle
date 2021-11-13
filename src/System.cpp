#include "System.h"

#include <cstdint>
#include <string>

namespace executor {
System::System(uint32_t cache_size, const std::string &readers_config,
               const std::string &writers_config, const std::string &items_file)
    : _file_storage(items_file), _cache(_file_storage, cache_size) {

  std::ifstream readers_input(readers_config);
  std::ifstream writers_input(writers_config);
  if (!readers_input) {
    throw std::runtime_error("Error opening readers config file" +
                             readers_config);
  }
  if (!writers_input) {
    throw std::runtime_error("Error opening writer config file" +
                             writers_config);
  }

  std::string str;

  while (std::getline(readers_input, str)) {
    _rCommandReaders.emplace_back(str);
    auto reader = std::make_shared<reader::Reader>(
        _cache, _rCommandReaders.back(), str + ".out");
    _readers.push_back(reader);
    _runner.addRunnable(reader);
  }

  while (std::getline(writers_input, str)) {
    _wCommandReaders.emplace_back(str);
    auto writer =
        std::make_shared<writer::Writer>(_cache, _wCommandReaders.back());
    _writers.push_back(writer);
    _runner.addRunnable(writer);
  }
}

void System::exec() {
  _runner.runAll();
  _runner.waitAllFinished();
}
} // namespace executor
