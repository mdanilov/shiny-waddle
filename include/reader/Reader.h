#ifndef GUARD_DE08D5CA_51E6_47E0_BCD2_F76F14CA9267
#define GUARD_DE08D5CA_51E6_47E0_BCD2_F76F14CA9267

#include "Command.h"
#include "IRunnable.h"
#include "command/ICommandStream.h"
#include "storage/IStorage.h"

#include <fstream>
#include <string>

namespace reader {
/**
 * \brief Reader. Implements IRunnable interface. Reads the values from Storage
 * by executing the commands read from the CommandReader and prints the result
 * to the output text file.
 *
 */
class Reader : public executor::IRunnable {
public:
  /**
   * \brief Construct a new Reader object
   *
   * @param storage reference to the storage
   * @param cmdReader reader command reader
   * @param output path to the output file
   */
  Reader(storage::IStorage &storage,
         command::ICommandStream<Command> &cmdReader, const std::string &output)
      : _storage(storage), _commandReader(cmdReader), _output(output){};

  /**
   * \brief Executes the reader logic.
   *
   */
  void execute() override;

private:
  storage::IStorage &_storage;
  command::ICommandStream<Command> &_commandReader;
  std::string _output;
};
} // namespace reader

#endif /* GUARD_DE08D5CA_51E6_47E0_BCD2_F76F14CA9267 */
