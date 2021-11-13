#ifndef GUARD_C555E4F4_F20C_4308_B353_1B075F9F93E7
#define GUARD_C555E4F4_F20C_4308_B353_1B075F9F93E7

#include "Command.h"
#include "command/ICommandStream.h"

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
class CommandStream : public command::ICommandStream<Command> {
public:
  static const uint32_t READ_ALL_COMMANDS = 0xFFFFFFFFU;

  /**
   * \brief Construct a new Command Reader object
   *
   * @param file path to the configuration file
   * @param bufferSize max number of the commands that can be read per step.
   */
  explicit CommandStream(std::string &file,
                         uint32_t bufferSize = READ_ALL_COMMANDS)
      : _config(file), _bufferSize(bufferSize), _line(0U) {}

  /**
   * \brief Open the file for reading.
   *
   *  @throws std::runtime_error if the file cannot be open
   */
  void open() override;

  /**
   * \brief Read the commands from the file. The number of the commands to read
   * is specified by the bufferSize parameter.
   *
   * The file stream should be opened before. If the file is closed empty array
   * is returned.
   *
   * All invalid commands are skipped.
   *
   * @return std::vector<Command> parsed reader commands
   */
  std::vector<Command> getCommands() override;

  /**
   * \brief Close the file stream.
   *
   */
  void close() override;

private:
  std::string _config;
  std::ifstream _stream;
  uint32_t _bufferSize;
  size_t _line;
};
} // namespace writer

#endif /* GUARD_C555E4F4_F20C_4308_B353_1B075F9F93E7 */
