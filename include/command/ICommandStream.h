#ifndef GUARD_DE6DA46E_07DD_491C_B59C_217AF57D1B5A
#define GUARD_DE6DA46E_07DD_491C_B59C_217AF57D1B5A

#include <vector>

namespace command {
/**
 * \brief ICommandStream interface allows to read the commands by chunks.
 *
 * \tparam Command type of the command object
 */
template <typename Command> class ICommandStream {
public:
  /**
   * \brief Open commands stream for reading.
   *
   */
  virtual void open() = 0;

  /**
   * \brief Requests the next commands.
   *
   * @return std::vector<Command> new commands, can be empty if there are no
   * more commands.
   */
  virtual std::vector<Command> getCommands() = 0;

  /**
   * \brief Close command stream.
   *
   */
  virtual void close() = 0;
};
} // namespace command

#endif /* GUARD_DE6DA46E_07DD_491C_B59C_217AF57D1B5A */
