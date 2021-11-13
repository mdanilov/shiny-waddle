cmake_minimum_required(VERSION 3.10)

project(MemoryFileCache)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(EXAMPLES_DIR ${PROJECT_SOURCE_DIR}/examples)
set(MOCK_DIR ${PROJECT_SOURCE_DIR}/mock)

file(GLOB_RECURSE LIB_SRC "src/*.cpp")
list(FILTER LIB_SRC EXCLUDE REGEX main.cpp)
add_library(memcache ${LIB_SRC})
target_include_directories(memcache PUBLIC include)
target_link_libraries(memcache PRIVATE Threads::Threads)

add_executable(executor "src/main.cpp")
target_link_libraries(executor PRIVATE memcache)

include(CTest)
enable_testing()

add_subdirectory(test)
