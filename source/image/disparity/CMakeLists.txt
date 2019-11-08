cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(disparity-estimation CXX)

set (CMAKE_CXX_STANDARD 14)

# disparity-estimation library
add_library(disparity-estimation SHARED disparity_estimation.cpp)
