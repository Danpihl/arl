
cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(math-core-tests CXX)

set (CMAKE_CXX_STANDARD 14)

set(TEST_CPP_FILES )

set(UTILS_TEST_FILES test_string.cpp
                     test_textfile.cpp
                     test_filesystem.cpp
                     test_misc.cpp
                     test_csv.cpp
                     test_algorithm.cpp
                     test_data_logger/test_data_logger_variable.cpp
                     test_data_logger/test_data_logger.cpp)
set(UTILS_SOURCE_FILES ${CMAKE_SOURCE_DIR}/source/utilities/string/string.cpp
                       ${CMAKE_SOURCE_DIR}/source/utilities/filesystem/filesystem.cpp
                       ${CMAKE_SOURCE_DIR}/source/utilities/textfile/textfile.cpp
                       ${CMAKE_SOURCE_DIR}/source/utilities/misc/misc.cpp
                       ${CMAKE_SOURCE_DIR}/source/utilities/csv/csv.cpp)

set(TEST_LIB_FILES libgtest.a
                   libgtest_main.a
                   pthread)

# test-utils executable
add_executable(test-utils ${UTILS_TEST_FILES} ${UTILS_SOURCE_FILES})
target_link_libraries(test-utils ${TEST_LIB_FILES} ${Boost_LIBRARIES})
