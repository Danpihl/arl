cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(clean-app)

add_executable(clean-app main.cpp)
target_link_libraries(clean-app arl-color-map
                                ${OpenCV_LIBS}
                                arl-opencv-wrapper)
#  ${Boost_LIBRARIES}