#ifndef GUARD_DE08D5CA_51E6_47E0_BCD2_F76F14CA9267
#define GUARD_DE08D5CA_51E6_47E0_BCD2_F76F14CA9267

#include "ICommandReader.h"
#include "IRunnable.h"
#include "storage/IStorage.h"

#include <fstream>
#include <string>

namespace reader {
class Reader : public executor::IRunnable {
public:
  Reader(storage::IStorage &storage, ICommandReader &cmdReader,
         const std::string &output)
      : _storage(storage), _commandReader(cmdReader), _output(output){};

  void execute() override;

private:
  storage::IStorage &_storage;
  ICommandReader &_commandReader;
  std::string _output;
};
} // namespace reader

#endif /* GUARD_DE08D5CA_51E6_47E0_BCD2_F76F14CA9267 */
