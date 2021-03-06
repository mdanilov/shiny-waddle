#include <gtest/gtest.h>

#include "writer/CommandStream.h"

TEST(WriterCommandStreamTest, basic) {
  std::string test_file("writer/CommandReaderTest.txt");

  writer::CommandStream reader(test_file);
  reader.open();
  std::vector<writer::Command> commands = reader.getCommands();
  EXPECT_EQ(commands.size(), 5);
  for (size_t i = 0; i < commands.size(); i++) {
    EXPECT_EQ(commands[i].index, i);
    EXPECT_EQ(commands[i].value, std::to_string((i + 1) * 100));
  }

  commands = reader.getCommands();
  EXPECT_EQ(commands.size(), 0);

  reader.close();
}

TEST(WriterCommandStreamTest, chunk_read) {
  std::string test_file("writer/CommandReaderTest.txt");

  writer::CommandStream reader(test_file, 3);
  reader.open();
  std::vector<writer::Command> commands = reader.getCommands();
  ASSERT_EQ(commands.size(), 3);
  for (size_t i = 0; i < commands.size(); i++) {
    EXPECT_EQ(commands[i].index, i);
    EXPECT_EQ(commands[i].value, std::to_string((i + 1) * 100));
  }

  commands = reader.getCommands();
  ASSERT_EQ(commands.size(), 2);
  EXPECT_EQ(commands[0].index, 3);
  EXPECT_EQ(commands[0].value, std::to_string(400));
  EXPECT_EQ(commands[1].index, 4);
  EXPECT_EQ(commands[1].value, std::to_string(500));

  reader.close();
}
