#ifndef GUARD_CCBD496C_BEAB_41F9_AF09_5E8E5E8855A2
#define GUARD_CCBD496C_BEAB_41F9_AF09_5E8E5E8855A2

#include "ICommandReader.h"
#include "IRunnable.h"
#include "storage/IStorage.h"

#include <string>

namespace writer {
class Writer : public executor::IRunnable {
public:
  Writer(storage::IStorage &storage, ICommandReader &cmdReader)
      : _storage(storage), _commandReader(cmdReader){};

  void execute() override;

private:
  storage::IStorage &_storage;
  ICommandReader &_commandReader;
};
} // namespace writer

#endif /* GUARD_CCBD496C_BEAB_41F9_AF09_5E8E5E8855A2 */
