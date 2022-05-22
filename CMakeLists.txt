cmake_minimum_required(VERSION 3.22)
project(laboratory)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/googletest)
add_subdirectory(lib/lbw)

add_executable(laboratory main.cpp)

include_directories(lib/googletest/googletest/include)

add_executable(Googletest Tests/testFraction.cpp Tests/testBitset.cpp Tests/testPrefixSum.cpp)
target_link_libraries(Googletest gtest gtest_main)
target_link_libraries(Googletest lbw)
