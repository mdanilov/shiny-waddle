#include <gtest/gtest.h>

#include "reader/CommandStream.h"

TEST(ReaderCommandStreamTest, basic) {
  std::string test_file("reader/CommandReaderTest.txt");

  reader::CommandStream reader(test_file);
  reader.open();
  std::vector<reader::Command> commands = reader.getCommands();
  EXPECT_EQ(commands.size(), 4);
  for (size_t i = 0; i < commands.size(); i++) {
    EXPECT_EQ(commands[i].index, i);
  }

  commands = reader.getCommands();
  EXPECT_EQ(commands.size(), 0);

  reader.close();
}

TEST(ReaderCommandStreamTest, chunk_read) {
  std::string test_file("reader/CommandReaderTest.txt");

  reader::CommandStream reader(test_file, 3);
  reader.open();
  std::vector<reader::Command> commands = reader.getCommands();
  ASSERT_EQ(commands.size(), 3);
  for (size_t i = 0; i < commands.size(); i++) {
    EXPECT_EQ(commands[i].index, i);
  }

  commands = reader.getCommands();
  ASSERT_EQ(commands.size(), 1);
  EXPECT_EQ(commands[0].index, 3);

  reader.close();
}
