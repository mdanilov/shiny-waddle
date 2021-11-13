#ifndef GUARD_CC78FF39_C201_4DF0_AD0A_09582B701211
#define GUARD_CC78FF39_C201_4DF0_AD0A_09582B701211

#include "Command.h"

#include <vector>

namespace writer {
class ICommandReader {
public:
  virtual void open() = 0;

  virtual std::vector<Command> nextCommands() = 0;

  virtual void close() = 0;
};
}

#endif /* GUARD_CC78FF39_C201_4DF0_AD0A_09582B701211 */
