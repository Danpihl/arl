cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(new-logging-app)

add_executable(new-logging-app main.cpp some_functions.cpp)
target_link_libraries(new-logging-app pthread)
