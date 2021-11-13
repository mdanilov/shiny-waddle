#ifndef GUARD_DA2CE42A_E96C_4117_A16A_E4BCE693DD5E
#define GUARD_DA2CE42A_E96C_4117_A16A_E4BCE693DD5E

#include <gmock/gmock.h>

#include "reader/ICommandReader.h"


#include <vector>

namespace reader {

class CommandReaderMock : public ICommandReader {
public:
  MOCK_METHOD0(open, void());
  MOCK_METHOD0(close, void());
  MOCK_METHOD0(nextCommands, std::vector<Command>());
};
} // namespace reader

#endif /* GUARD_DA2CE42A_E96C_4117_A16A_E4BCE693DD5E */
