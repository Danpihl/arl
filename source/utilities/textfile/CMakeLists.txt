cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(arl-textfile CXX)

set (CMAKE_CXX_STANDARD 14)

# arl-textfile library
add_library(arl-textfile SHARED textfile.cpp)
target_link_libraries(arl-textfile arl-string arl-filesystem)
