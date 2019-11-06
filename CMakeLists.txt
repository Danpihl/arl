cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(arl CXX)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wno-deprecated \
    -Wall -Wextra -pedantic -fdiagnostics-color")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")
endif()
# -fprofile-arcs -ftest-coverage

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(cotire)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories("${EIGEN3_INCLUDE_DIR}")

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/gtest/build/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/gtest/googletest/include)

# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/rapidcheck/build)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/rapidcheck/include)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/rapidcheck/extras/gtest/include)

find_package(OpenCV REQUIRED)
find_package(Boost 1.58.0 REQUIRED
             COMPONENTS
             filesystem
             system
             program_options
             thread
             log)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
include_directories(${Boost_INCLUDE_DIRS})


add_subdirectory(apps/clean_application)
add_subdirectory(apps/new_logging_test)
add_subdirectory(apps/test_image_application)

add_subdirectory(source/utilities/string)
add_subdirectory(source/utilities/filesystem)
add_subdirectory(source/utilities/csv)
add_subdirectory(source/utilities/color_map)
add_subdirectory(source/utilities/textfile)
add_subdirectory(source/utilities/misc)

add_subdirectory(source/image/opencv_wrapper)

add_subdirectory(test/unit_tests/math)
add_subdirectory(test/unit_tests/utils)

add_custom_target(tests)
add_dependencies(tests test-math-core test-utils)
