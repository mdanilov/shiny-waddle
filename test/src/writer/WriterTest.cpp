#include "storage/StorageMock.h"
#include "writer/CommandReaderMock.h"

#include "writer/Writer.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace writer {

TEST(WriterTest, basic) {
  std::vector<Command> commands = {{1, "100"}, {2, "200"}, {3, "300"}};
  storage::StorageMock storageMock;
  CommandReaderMock commandReaderMock;

  Writer writer(storageMock, commandReaderMock);
  EXPECT_CALL(storageMock, writeByIndex(1, "100")).Times(1);
  EXPECT_CALL(storageMock, writeByIndex(2, "200")).Times(1);
  EXPECT_CALL(storageMock, writeByIndex(3, "300")).Times(1);
  EXPECT_CALL(commandReaderMock, open()).Times(1);
  EXPECT_CALL(commandReaderMock, close()).Times(1);
  EXPECT_CALL(commandReaderMock, nextCommands())
      .WillOnce(Return(commands))
      .WillRepeatedly(Return(std::vector<Command>()));
  writer.execute();
}

} // namespace writer
