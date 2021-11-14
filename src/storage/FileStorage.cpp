#include "storage/FileStorage.h"

#include <cstdio>
#include <fstream>
#include <iostream>

namespace storage {
ReadResult FileStorage::readByIndex(Index index) {
  std::shared_lock<std::shared_timed_mutex> lock(_mutex);
  std::ifstream in(_file);
  std::string str;
  Index cur = 0U;
  while (std::getline(in, str) && cur < index) {
    cur++;
  }

  if (cur != index) {
    std::cout << "Cache: warning, read index is out of range " << index
              << std::endl;
    return ReadResult(std::string(""));
  }

  return str;
}

void FileStorage::writeByIndex(Index index, const Value &val) {
  std::unique_lock<std::shared_timed_mutex> lock(_mutex);

  std::ifstream in(_file);
  if (!in) {
    std::cout << "Writer: Error opening file " << _file << std::endl;
    return;
  }
  std::string temp_name = std::tmpnam(nullptr);
  std::ofstream out(temp_name);
  if (!out) {
    std::cout << "Writer: Error creating temporary file " << temp_name
              << std::endl;
    return;
  }

  std::string str;
  Index cur = 0U;
  while (std::getline(in, str)) {
    if (cur == index) {
      str = val;
    }
    str += "\n";
    cur++;
    out << str;
  }

  if (cur < index) {
    std::remove(temp_name.c_str());
    std::cout << "Writer: Index is out of range " << index << std::endl;
    return;
  }

  if (std::remove(_file.c_str()) != 0) {
    std::remove(temp_name.c_str());
    std::cout << "FileStorage: Error while removing the file " + _file
              << std::endl;
    return;
  }

  if (std::rename(temp_name.c_str(), _file.c_str()) != 0) {
    throw std::runtime_error("FileStorage: Error while renaming the file " +
                             temp_name);
  };
}
} // namespace storage