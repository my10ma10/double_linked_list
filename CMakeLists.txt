cmake_minimum_required(VERSION 3.16)
project(list)

add_subdirectory(extern/googletest)
include_directories(${CMAKE_SOURCE_DIR}/extern/googletest/googletest/include)

enable_testing()
add_test(NAME ListUnitTests, COMMAND list_test)



