#ifndef GUARD_B5F99602_E18F_4094_9B39_E20472FF5390
#define GUARD_B5F99602_E18F_4094_9B39_E20472FF5390

#include "Command.h"

#include <vector>

namespace reader {
/**
 * \brief ICommandReader interface. Used by the Reader to read the commands
 *
 */
class ICommandReader {
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
  virtual std::vector<Command> nextCommands() = 0;

  /**
   * \brief Close command stream.
   *
   */
  virtual void close() = 0;
};
} // namespace reader

#endif /* GUARD_B5F99602_E18F_4094_9B39_E20472FF5390 */
