#ifndef GUARD_B5F99602_E18F_4094_9B39_E20472FF5390
#define GUARD_B5F99602_E18F_4094_9B39_E20472FF5390

#include "Command.h"

#include <vector>

namespace reader {
class ICommandReader {
public:
  virtual void open() = 0;

  virtual std::vector<Command> nextCommands() = 0;

  virtual void close() = 0;
};
} // namespace reader

#endif /* GUARD_B5F99602_E18F_4094_9B39_E20472FF5390 */
