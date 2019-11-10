cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(commandline-colors CXX)

set (CMAKE_CXX_STANDARD 14)

# commandline-colors library
add_library(commandline-colors SHARED commandline_colors.cpp)
