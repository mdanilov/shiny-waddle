#ifndef GUARD_F6A3E6AA_21F5_4990_85BA_9BE13E67CE35
#define GUARD_F6A3E6AA_21F5_4990_85BA_9BE13E67CE35

#include "Command.h"
#include "ICommandReader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace reader {
class CommandReader : public ICommandReader {
public:
  static const uint32_t READ_ALL_COMMANDS = 0xFFFFFFFFU;

  explicit CommandReader(std::string &file,
                         uint32_t bufferSize = READ_ALL_COMMANDS)
      : _config(file), _bufferSize(bufferSize), _line(0U) {}

  void open() override;

  std::vector<Command> nextCommands() override;

  void close() override;

private:
  std::string _config;
  std::ifstream _stream;
  uint32_t _bufferSize;
  size_t _line;
};
} // namespace reader

#endif /* GUARD_F6A3E6AA_21F5_4990_85BA_9BE13E67CE35 */
