cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(string-utils CXX)

set (CMAKE_CXX_STANDARD 14)

# misc-utils library
add_library(misc-utils SHARED misc_utils.cpp)
