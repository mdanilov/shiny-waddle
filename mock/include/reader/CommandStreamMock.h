#ifndef GUARD_DA2CE42A_E96C_4117_A16A_E4BCE693DD5E
#define GUARD_DA2CE42A_E96C_4117_A16A_E4BCE693DD5E

#include <gmock/gmock.h>

#include "command/ICommandStream.h"
#include "reader/Command.h"

#include <vector>

namespace reader {

class CommandStreamMock : public command::ICommandStream<Command> {
public:
  MOCK_METHOD0(open, void());
  MOCK_METHOD0(close, void());
  MOCK_METHOD0(getCommands, std::vector<Command>());
};
} // namespace reader

#endif /* GUARD_DA2CE42A_E96C_4117_A16A_E4BCE693DD5E */
