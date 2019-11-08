cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(textfile-reader CXX)

set (CMAKE_CXX_STANDARD 14)

# textfile-utils library
add_library(textfile-utils SHARED textfile_utils.cpp)
target_link_libraries(textfile-utils string-utils)
