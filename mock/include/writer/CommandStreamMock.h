#ifndef GUARD_A1E0CCE7_565B_4E3C_B803_E750A2AD0175
#define GUARD_A1E0CCE7_565B_4E3C_B803_E750A2AD0175

#include <gmock/gmock.h>

#include "command/ICommandStream.h"
#include "writer/Command.h"

#include <vector>

namespace writer {

class CommandStreamMock : public command::ICommandStream<Command> {
public:
  MOCK_METHOD0(open, void());
  MOCK_METHOD0(close, void());
  MOCK_METHOD0(getCommands, std::vector<Command>());
};
} // namespace writer

#endif /* GUARD_A1E0CCE7_565B_4E3C_B803_E750A2AD0175 */
