#ifndef GUARD_F6A3E6AA_21F5_4990_85BA_9BE13E67CE35
#define GUARD_F6A3E6AA_21F5_4990_85BA_9BE13E67CE35

#include "Command.h"
#include "command/FileCommandStream.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace reader {
/**
 * \brief The CommandStream implements the reading of the Reader commands from
 * the configuration text file.
 *
 * Each line of the text file should contains 1-based index number.
 *
 * Example of the file:
 * 1
 * 2
 * 3
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
} // namespace reader

#endif /* GUARD_F6A3E6AA_21F5_4990_85BA_9BE13E67CE35 */
