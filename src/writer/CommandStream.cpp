#include "writer/CommandStream.h"

#include <iostream>
#include <iterator>
#include <sstream>

namespace writer {

Command CommandStream::parse(const std::string &str) {
  Command command;
  std::vector<std::string> tokens;
  std::istringstream iss(str);
  std::copy(std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(), std::back_inserter(tokens));
  if (tokens.size() != 2) {
    throw std::exception();
  }
  uint32_t index = 0U;
  index = std::stoul(tokens[0]);
  if (index == 0) {
    throw std::exception();
  }
  command.index = index - 1;
  command.value = tokens[1];
  return command;
}

} // namespace writer
