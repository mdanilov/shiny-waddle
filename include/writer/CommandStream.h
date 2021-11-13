#ifndef GUARD_C555E4F4_F20C_4308_B353_1B075F9F93E7
#define GUARD_C555E4F4_F20C_4308_B353_1B075F9F93E7

#include "Command.h"
#include "command/FileCommandStream.h"

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace writer {
/**
 * \brief The CommandStream implements the reading of the Writer commands from
 * the configuration text file.
 *
 * Each line of the text file should contains 1-based index number and the
 * string value.
 *
 * Example of the file:
 * 1 100
 * 2 200
 * 3 300
 * ..
 *
 * If the configuration file is too big the user can specify the maximum number
 * of the lines to read in the ctr. By default all commands are read.
 *
 */
class CommandStream : public command::FileCommandStream<Command> {
public:
  /**
   * \brief Construct a new Command Stream object
   *
   * @param file path to the configuration file
   * @param bufferSize max number of the commands that can be read per step.
   */
  explicit CommandStream(std::string &file,
                         uint32_t bufferSize = command::READ_ALL_COMMANDS)
      : command::FileCommandStream<Command>(file, bufferSize) {}

protected:
  Command parse(const std::string &str) override;
};
} // namespace writer

#endif /* GUARD_C555E4F4_F20C_4308_B353_1B075F9F93E7 */
