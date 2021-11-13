#ifndef GUARD_CCBD496C_BEAB_41F9_AF09_5E8E5E8855A2
#define GUARD_CCBD496C_BEAB_41F9_AF09_5E8E5E8855A2

#include "ICommandReader.h"
#include "IRunnable.h"
#include "storage/IStorage.h"

#include <string>

namespace writer {
/**
 * \brief Writer. Implements IRunnable interface. Writes values to the Storage
 * by executing the commands read from the CommandReader.
 *
 */
class Writer : public executor::IRunnable {
public:
  /**
   * \brief Construct a new Writer object
   *
   * @param storage reference to the storage
   * @param cmdReader reader command reader
   */
  Writer(storage::IStorage &storage, ICommandReader &cmdReader)
      : _storage(storage), _commandReader(cmdReader){};

  /**
   * \brief Executes the writer logic.
   *
   */
  void execute() override;

private:
  storage::IStorage &_storage;
  ICommandReader &_commandReader;
};
} // namespace writer

#endif /* GUARD_CCBD496C_BEAB_41F9_AF09_5E8E5E8855A2 */
