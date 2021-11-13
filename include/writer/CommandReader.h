#ifndef GUARD_C555E4F4_F20C_4308_B353_1B075F9F93E7
#define GUARD_C555E4F4_F20C_4308_B353_1B075F9F93E7

#include "Command.h"
#include "ICommandReader.h"

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace writer {
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
} // namespace writer

#endif /* GUARD_C555E4F4_F20C_4308_B353_1B075F9F93E7 */
