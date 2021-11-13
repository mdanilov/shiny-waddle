#ifndef GUARD_A83F1562_EDC7_4152_AA43_0077EFB517D9
#define GUARD_A83F1562_EDC7_4152_AA43_0077EFB517D9

#include "ICommandStream.h"

#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>

namespace command {

static const uint32_t READ_ALL_COMMANDS = 0xFFFFFFFFU;

template <typename Command>
class FileCommandStream : public ICommandStream<Command> {
public:
  FileCommandStream(std::string &file, uint32_t bufferSize = READ_ALL_COMMANDS)
      : _config(file), _bufferSize(bufferSize), _line(0U) {}

  /**
   * \brief Open the file for reading.
   *
   *  @throws std::runtime_error if the file cannot be open
   */
  void open() override {
    _stream.open(_config, std::ifstream::in);
    if (!_stream) {
      throw std::runtime_error("Error opening command config file " + _config);
    }
    _line = 0U;
  }

  /**
   * \brief Close the file stream.
   *
   */
  void close() override { _stream.close(); }

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
  std::vector<Command> getCommands() override {
    std::vector<Command> commands;
    if (!_stream) {
      return commands;
    }

    std::string str;
    while (commands.size() < _bufferSize && std::getline(_stream, str)) {
      _line++;
      try {
        Command cmd = parse(str);
        commands.push_back(cmd);
      } catch (std::exception const &ex) {
        std::cout << "FileCommandStream: Invalid command at " << _line << "in file "
                  << _config << std::endl;
      }
    }
    return commands;
  }

protected:
  virtual Command parse(const std::string &str) = 0;

private:
  std::string _config;
  std::ifstream _stream;
  uint32_t _bufferSize;
  size_t _line;
};
} // namespace command

#endif /* GUARD_A83F1562_EDC7_4152_AA43_0077EFB517D9 */
