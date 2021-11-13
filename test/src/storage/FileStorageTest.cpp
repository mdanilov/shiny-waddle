#include <gtest/gtest.h>

#include "storage/FileStorage.h"

#include <fstream>
#include <string>

using namespace ::testing;

namespace storage {

TEST(FileStorageTest, basic) {
  std::string filename = std::tmpnam(nullptr);
  {
    std::ofstream test_file(filename);
    std::string content = "test2\ntest3\ntest4\n";
    test_file << content;
  }

  FileStorage file_storage(filename);

  ReadResult result = file_storage.readByIndex(0);
  EXPECT_EQ(result.value, "test2");
  result = file_storage.readByIndex(1);
  EXPECT_EQ(result.value, "test3");
  result = file_storage.readByIndex(2);
  EXPECT_EQ(result.value, "test4");

  file_storage.writeByIndex(0, "test1");

  {
    std::ifstream test_file(filename);
    std::string content((std::istreambuf_iterator<char>(test_file)),
                        std::istreambuf_iterator<char>());
    EXPECT_EQ(content, "test1\ntest3\ntest4\n");
  }
}

} // namespace storage
