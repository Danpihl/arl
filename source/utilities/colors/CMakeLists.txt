cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(colors CXX)

set (CMAKE_CXX_STANDARD 14)

# colors library
add_library(colors SHARED colors.cpp)
