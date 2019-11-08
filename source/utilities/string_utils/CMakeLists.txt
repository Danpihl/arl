cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(string-utils CXX)

set (CMAKE_CXX_STANDARD 14)

# string-utils library
add_library(string-utils SHARED string_utils.cpp)
