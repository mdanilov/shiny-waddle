project(googletest-git NONE)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TESTS_SRC "src/*.cpp")
add_executable(tests ${TESTS_SRC})
target_link_libraries(tests gtest gmock_main memcache)
target_include_directories(tests PRIVATE ${MOCK_DIR}/include)

add_test(NAME tests COMMAND tests WORKING_DIRECTORY ${EXAMPLES_DIR}/test)
