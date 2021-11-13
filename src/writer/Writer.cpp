#include "writer/Writer.h"

#include <cstdint>
#include <fstream>
#include <vector>

namespace writer {

void Writer::execute() {
  _commandReader.open();
  std::vector<Command> commands = _commandReader.getCommands();
  while (commands.size() > 0) {
    for (size_t i = 0; i < commands.size(); ++i) {
      Command &command = commands[i];
      _storage.writeByIndex(command.index, command.value);
    }
    commands = _commandReader.getCommands();
  }
  _commandReader.close();
}
} // namespace writer
