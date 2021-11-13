#include "reader/CommandReader.h"

namespace reader {
void CommandReader::open() {
  _stream.open(_config, std::ifstream::in);
  if (!_stream) {
    throw std::runtime_error("Error opening command config file " + _config);
  }
  _line = 0U;
}

std::vector<Command> CommandReader::nextCommands() {
  std::vector<Command> commands;
  std::string str;
  while (commands.size() < _bufferSize && std::getline(_stream, str)) {
    _line++;
    try {
      uint32_t index = std::stoul(str);
      commands.push_back({index});
    } catch (std::exception const &ex) {
      std::cout << "Reader: Invalid index at line " << _line << "in file "
                << _config << std::endl;
    }
  }
  return commands;
}

void CommandReader::close() { _stream.close(); }
} // namespace reader
