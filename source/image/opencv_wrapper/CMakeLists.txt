cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(opencv-wrapper CXX)

find_package(OpenCV REQUIRED)

set(WRAPPER_SOURCE_FILES opencv_wrapper.cpp)

add_library(opencv-wrapper SHARED ${WRAPPER_SOURCE_FILES})
target_link_libraries(opencv-wrapper ${OpenCV_LIBS})
# set_target_properties(opencv-wrapper PROPERTIES LINKER_LANGUAGE CXX)
