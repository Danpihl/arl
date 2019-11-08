cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(csv-utils CXX)

set (CMAKE_CXX_STANDARD 14)

# csv-utils library
add_library(csv-utils SHARED csv_utils.cpp)
target_link_libraries(csv-utils textfile-utils string-utils)
