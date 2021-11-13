#ifndef GUARD_CC78FF39_C201_4DF0_AD0A_09582B701211
#define GUARD_CC78FF39_C201_4DF0_AD0A_09582B701211

#include "Command.h"

#include <vector>

namespace writer {
/**
 * \brief ICommandReader interface. Used by the Writer to read the commands
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
}

#endif /* GUARD_CC78FF39_C201_4DF0_AD0A_09582B701211 */
