#include <cstdlib>
#include <iostream>
#include <string>

#include "System.h"

int main(int argc, char **argv) {
  static const int EXPECTED_ARGS = 5U;
  if (argc < EXPECTED_ARGS) {
    std::cout << "Wrong number of arguments"
              << ", expected " << EXPECTED_ARGS << ", but got " << argc
              << std::endl;
    exit(EXIT_FAILURE);
  }

  int32_t cache_size = 0U;
  try {
    cache_size = std::stoi(std::string(argv[1]));
  } catch (const std::invalid_argument &ia) {
    std::cout << "Cache size argument should be integer value" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string reader_config(argv[2]);
  std::string writer_config(argv[3]);
  std::string items_file(argv[4]);

  try {
    executor::System system(cache_size, reader_config, writer_config,
                            items_file);
    system.exec();
  } catch (std::exception const &ex) {
    std::cout << "System error: " << ex.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  return 0;
}
