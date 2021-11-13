#include <gtest/gtest.h>

#include "reader/CommandReader.h"

TEST(ReaderCommandReaderTest, basic) {
  std::string test_file("reader/CommandReaderTest.txt");

  reader::CommandReader reader(test_file);
  reader.open();
  std::vector<reader::Command> commands = reader.nextCommands();
  EXPECT_EQ(commands.size(), 4);
  for (size_t i = 0; i < commands.size(); i++) {
    EXPECT_EQ(commands[i].index, i);
  }

  commands = reader.nextCommands();
  EXPECT_EQ(commands.size(), 0);

  reader.close();
}

TEST(ReaderCommandReaderTest, chunk_read) {
  std::string test_file("reader/CommandReaderTest.txt");

  reader::CommandReader reader(test_file, 3);
  reader.open();
  std::vector<reader::Command> commands = reader.nextCommands();
  ASSERT_EQ(commands.size(), 3);
  for (size_t i = 0; i < commands.size(); i++) {
    EXPECT_EQ(commands[i].index, i);
  }

  commands = reader.nextCommands();
  ASSERT_EQ(commands.size(), 1);
  EXPECT_EQ(commands[0].index, 3);

  reader.close();
}
