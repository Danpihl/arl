#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "arl/utilities/filesystem_utils.h"
#include "arl/utilities/logging.h"
#include "arl/utilities/string_utils.h"

namespace arl
{
class FilesystemUtilsTest : public testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(FilesystemUtilsTest, TestIsDir)
{
    const std::string dir_path = "../test/unit_tests/utils/test_data/a_directory";
    const std::string file_path = "../test/unit_tests/utils/test_data/a_directory/a_file";

    ASSERT_TRUE(isDirectory(dir_path));
    ASSERT_FALSE(isDirectory(file_path));

    ASSERT_FALSE(isFile(dir_path));
    ASSERT_TRUE(isFile(file_path));
}

}  // namespace arl
