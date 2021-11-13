#include "writer/CommandReader.h"

#include <iostream>
#include <iterator>
#include <sstream>

namespace writer {

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
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(), std::back_inserter(tokens));
    if (tokens.size() != 2) {
      std::cout << "Writer: Wrong command at line " << _line << "in file "
                << _config << std::endl;
      continue;
    }

    uint32_t index = 0U;
    try {
      index = std::stoul(tokens[0]);
      if (index == 0) {
        throw std::exception();
      }
    } catch (std::exception const &ex) {
      std::cout << "Writer: Invalid index at line " << _line << "in file "
                << _config << std::endl;
      continue;
    }

    commands.push_back({index - 1, tokens[1]});
  }
  return commands;
}

void CommandReader::close() { _stream.close(); }
}
