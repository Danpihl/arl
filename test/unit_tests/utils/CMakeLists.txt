
cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(math-core-tests CXX)

set (CMAKE_CXX_STANDARD 14)

set(TEST_CPP_FILES )

set(UTILS_TEST_FILES test_string_utils.cpp)
set(UTILS_SOURCE_FILES ${CMAKE_SOURCE_DIR}/source/utilities/string_utils/string_utils.cpp
                        ${CMAKE_SOURCE_DIR}/source/utilities/filesystem/filesystem_utils.cpp)

set(TEST_LIB_FILES libgtest.a
                   libgtest_main.a
                   pthread)

# test-utils executable
add_executable(test-utils ${UTILS_TEST_FILES} ${UTILS_SOURCE_FILES})
target_link_libraries(test-utils ${TEST_LIB_FILES})

# Individual targets
# add_executable(test-math-core-gen-matrix-math test_general_matrix_math_functions.cpp ${TEST_UTILS_FILES})
# target_link_libraries(test-math-core-gen-matrix-math ${TEST_LIB_FILES})
