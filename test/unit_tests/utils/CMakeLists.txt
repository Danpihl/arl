
cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(math-core-tests CXX)

set (CMAKE_CXX_STANDARD 14)

set(TEST_CPP_FILES )

set(UTILS_TEST_FILES test_string_utils.cpp
                     test_textfile_utils.cpp
                     test_filesystem_utils.cpp
                     test_misc_utils.cpp
                     test_csv_utils.cpp)
set(UTILS_SOURCE_FILES ${CMAKE_SOURCE_DIR}/source/utilities/string_utils/string_utils.cpp
                       ${CMAKE_SOURCE_DIR}/source/utilities/filesystem/filesystem_utils.cpp
                       ${CMAKE_SOURCE_DIR}/source/utilities/textfile_utils/textfile_utils.cpp
                       ${CMAKE_SOURCE_DIR}/source/utilities/misc_utils/misc_utils.cpp
                       ${CMAKE_SOURCE_DIR}/source/utilities/csv_utils/csv_utils.cpp)

set(TEST_LIB_FILES libgtest.a
                   libgtest_main.a
                   pthread)

# test-utils executable
add_executable(test-utils ${UTILS_TEST_FILES} ${UTILS_SOURCE_FILES})
target_link_libraries(test-utils ${TEST_LIB_FILES} ${Boost_LIBRARIES})
