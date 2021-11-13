#include "storage/StorageMock.h"
#include "reader/CommandReaderMock.h"

#include "reader/Reader.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace reader {

TEST(ReaderTest, basic) {
    std::string test_output("out/ReaderTest.out.txt");
    std::vector<Command> commands = {{1}, {2}, {3}};
    storage::StorageMock storageMock;
    CommandReaderMock commandReaderMock;

    Reader reader(storageMock, commandReaderMock, test_output);
    EXPECT_CALL(storageMock, readByIndex(1))
        .Times(1)
        .WillOnce(Return(storage::ReadResult{std::string("1"), false}));
    EXPECT_CALL(storageMock, readByIndex(2))
        .Times(1)
        .WillOnce(
            Return(storage::ReadResult{std::string("2"), true}));
    EXPECT_CALL(storageMock, readByIndex(3))
        .Times(1)
        .WillOnce(Return(storage::ReadResult{std::string("2"), false}));
    EXPECT_CALL(commandReaderMock, open()).Times(1);
    EXPECT_CALL(commandReaderMock, close()).Times(1);
    EXPECT_CALL(commandReaderMock, nextCommands())
        .WillOnce(Return(commands))
        .WillRepeatedly(Return(std::vector<Command>()));
    reader.execute();
}

}
