#include "storage/StorageMock.h"
#include "writer/CommandStreamMock.h"

#include "writer/Writer.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace writer {

TEST(WriterTest, basic) {
  std::vector<Command> commands = {{1, "100"}, {2, "200"}, {3, "300"}};
  storage::StorageMock storageMock;
  CommandStreamMock commandStreamMock;

  Writer writer(storageMock, commandStreamMock);
  EXPECT_CALL(storageMock, writeByIndex(1, "100")).Times(1);
  EXPECT_CALL(storageMock, writeByIndex(2, "200")).Times(1);
  EXPECT_CALL(storageMock, writeByIndex(3, "300")).Times(1);
  EXPECT_CALL(commandStreamMock, open()).Times(1);
  EXPECT_CALL(commandStreamMock, close()).Times(1);
  EXPECT_CALL(commandStreamMock, getCommands())
      .WillOnce(Return(commands))
      .WillRepeatedly(Return(std::vector<Command>()));
  writer.execute();
}

} // namespace writer
