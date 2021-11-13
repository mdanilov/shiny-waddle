#ifndef GUARD_A1E0CCE7_565B_4E3C_B803_E750A2AD0175
#define GUARD_A1E0CCE7_565B_4E3C_B803_E750A2AD0175

#include <gmock/gmock.h>

#include "writer/ICommandReader.h"

#include <vector>

namespace writer {

class CommandReaderMock : public ICommandReader {
public:
  MOCK_METHOD0(open, void());
  MOCK_METHOD0(close, void());
  MOCK_METHOD0(nextCommands, std::vector<Command>());
};
} // namespace writer

#endif /* GUARD_A1E0CCE7_565B_4E3C_B803_E750A2AD0175 */
