#include "reader/CommandStreamMock.h"
#include "storage/StorageMock.h"

#include "reader/Reader.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace reader {

TEST(ReaderTest, basic) {
    std::string test_output("out/ReaderTest.out.txt");
    std::vector<Command> commands = {{1}, {2}, {3}};
    storage::StorageMock storageMock;
    CommandStreamMock commandStreamMock;

    Reader reader(storageMock, commandStreamMock, test_output);
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
    EXPECT_CALL(commandStreamMock, open()).Times(1);
    EXPECT_CALL(commandStreamMock, close()).Times(1);
    EXPECT_CALL(commandStreamMock, getCommands())
        .WillOnce(Return(commands))
        .WillRepeatedly(Return(std::vector<Command>()));
    reader.execute();
}

}
