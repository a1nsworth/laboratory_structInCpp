cmake_minimum_required(VERSION 3.22)
project(laboratory)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/googletest)

add_executable(laboratory main.cpp)

include_directories(lib/googletest/googletest/include)
add_executable(Googletest Tests/testBitset.cpp)

target_link_libraries(Googletest gtest gtest_main main.cpp)