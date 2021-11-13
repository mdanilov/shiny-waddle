#include "reader/CommandStream.h"

namespace reader {

Command CommandStream::parse(const std::string &str) {
  Command command;
  uint32_t index = std::stoul(str);
  if (index == 0) {
    throw std::exception();
  }
  command.index = index - 1;
  return command;
}
} // namespace reader
