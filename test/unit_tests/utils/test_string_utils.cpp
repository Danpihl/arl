#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "arl/utilities/filesystem_utils.h"
#include "arl/utilities/string_utils.h"

namespace arl
{
class StringUtilsTest : public testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(StringUtilsTest, TestJoinPathsNoSlash)
{
    const std::string path0 = "/path/to/a/folder";
    const std::string path1 = "another/path";
    const std::string joined_path_exp = path0 + "/" + path1;
    const std::string joined_path_act = joinPaths(path0, path1);
    ASSERT_EQ(joined_path_exp, joined_path_act);
}

TEST_F(StringUtilsTest, TestJoinPathsSlash)
{
    const std::string path0 = "/path/to/a/folder/";
    const std::string path1 = "another/path";
    const std::string joined_path_exp = path0 + path1;
    const std::string joined_path_act = joinPaths(path0, path1);
    ASSERT_EQ(joined_path_exp, joined_path_act);
}

TEST_F(StringUtilsTest, TestSplitString)
{
    const std::string s0 = "f4oim,g43rf,22f,hw4";
    const std::vector<std::string> split_str_exp = {"f4oim", "g43rf", "22f", "hw4"};
    const std::vector<std::string> split_str_act = splitString(s0, ",");

    ASSERT_EQ(split_str_exp.size(), split_str_act.size());

    for (size_t k = 0; k < split_str_exp.size(); k++)
    {
        ASSERT_EQ(split_str_exp[k], split_str_act[k]);
    }
}

TEST_F(StringUtilsTest, TestSplitString1)
{
    const std::string s0 = "f4oim,g43rf,22f,hw4,,";
    const std::vector<std::string> split_str_exp = {"f4oim", "g43rf", "22f", "hw4"};
    const std::vector<std::string> split_str_act = splitString(s0, ",");

    // ASSERT_EQ(split_str_exp.size(), split_str_act.size());

    for (size_t k = 0; k < split_str_exp.size(); k++)
    {
        // ASSERT_EQ(split_str_exp[k], split_str_act[k]);
        std::cout << split_str_act[k] << std::endl;
    }
}

}  // namespace arl
