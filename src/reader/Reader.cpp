#include "reader/Reader.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

namespace reader {

void Reader::execute() {
  std::ofstream out(_output);
  if (!out) {
    std::cout << "Reader: Error opening file " << _output << std::endl;
    return;
  }

  _commandReader.open();
  std::vector<Command> commands = _commandReader.nextCommands();
  while (commands.size() > 0) {
    for (size_t i = 0; i < commands.size(); ++i) {
      Command &command = commands[i];
      storage::ReadResult res = _storage.readByIndex(command.index);
      out << res.value << " " << (res.cache_miss ? "Disk" : "Cache")
          << std::endl;
    }
    commands = _commandReader.nextCommands();
  }
  _commandReader.close();
}
} // namespace reader
