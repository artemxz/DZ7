cmake_minimum_required(VERSION 3.14)
project(DZ7_Containers_Tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(containers_tests array_tests.cpp list_tests.cpp)

target_link_libraries(containers_tests gtest_main)

enable_testing()
add_test(NAME AllTests COMMAND containers_tests)