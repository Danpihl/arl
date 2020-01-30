cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(filesystem-utils CXX)

set (CMAKE_CXX_STANDARD 14)

# filesystem-utils library
add_library(filesystem-utils SHARED filesystem_utils.cpp)
target_link_libraries(filesystem-utils ${Boost_LIBRARIES})
