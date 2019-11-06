cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project(arl-opencv-wrapper CXX)

find_package(OpenCV REQUIRED)

set(WRAPPER_SOURCE_FILES opencv_wrapper.cpp)

add_library(arl-opencv-wrapper SHARED ${WRAPPER_SOURCE_FILES})
target_link_libraries(arl-opencv-wrapper ${OpenCV_LIBS}
                                         arl-color-map)
# set_target_properties(opencv-wrapper PROPERTIES LINKER_LANGUAGE CXX)
