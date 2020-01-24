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

#include "string_test_data.h"
#include "utils_test_utilities.h"

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
    ASSERT_STD_VEC_EQ_STD_VEC(split_str_exp, split_str_act);
}

TEST_F(StringUtilsTest, TestSplitString1)
{
    const std::string s0 = "f4oim,g43rf,22f,hw4,,";
    const std::vector<std::string> split_str_exp = {"f4oim", "g43rf", "22f", "hw4", "", ""};
    const std::vector<std::string> split_str_act = splitString(s0, ",");

    ASSERT_EQ(split_str_exp.size(), split_str_act.size());

    ASSERT_STD_VEC_EQ_STD_VEC(split_str_exp, split_str_act);
}

TEST_F(StringUtilsTest, TestFindSubStringIndices)
{
    const std::string s0 = "micdfacdeorcdmmacdfcdcdoacd";
    const std::string sub_str = "cd";

    const std::vector<size_t> indices_exp = {2, 6, 11, 16, 19, 21, 25};
    const std::vector<size_t> indices_act = findSubStringIndices(s0, sub_str);
    ASSERT_STD_VEC_EQ_STD_VEC(indices_exp, indices_act);
}

TEST_F(StringUtilsTest, TestFindSubStringIndicesEmpty)
{
    const std::string s0 = "micdfacdeorcdmmacdfcdcdoacd";
    const std::string sub_str = "cdq";

    const std::vector<size_t> indices_exp;
    const std::vector<size_t> indices_act = findSubStringIndices(s0, sub_str);
    ASSERT_EQ(indices_exp.size(), indices_act.size());
}

TEST_F(StringUtilsTest, TestFindSubStringIndices1)
{
    const std::vector<size_t> indices0 = findSubStringIndices("jd", "ade");
    ASSERT_EQ(indices0.size(), static_cast<size_t>(0));

    const std::vector<size_t> indices1 = findSubStringIndices("jdq", "jdq");
    ASSERT_EQ(indices1.size(), static_cast<size_t>(1));
    ASSERT_EQ(indices1[0], static_cast<size_t>(0));
}

TEST_F(StringUtilsTest, TestSplitStringOneSpace)
{
    const std::string s0 = " AaaABbbBCccC";
    const std::string s1 = "AaaA BbbBCccC";
    const std::string s2 = "AaaABbbB CccC";
    const std::string s3 = "AaaABbbBCccC ";
    const std::string s4 = "AaaABbbBCccC";
    const std::string delim = " ";
    const std::vector<std::string> split_string0 = splitString(s0, delim);
    const std::vector<std::string> split_string1 = splitString(s1, delim);
    const std::vector<std::string> split_string2 = splitString(s2, delim);
    const std::vector<std::string> split_string3 = splitString(s3, delim);
    const std::vector<std::string> split_string4 = splitString(s4, delim);

    const std::vector<std::string> split_string0_exp = {"", "AaaABbbBCccC"};
    const std::vector<std::string> split_string1_exp = {"AaaA", "BbbBCccC"};
    const std::vector<std::string> split_string2_exp = {"AaaABbbB", "CccC"};
    const std::vector<std::string> split_string3_exp = {"AaaABbbBCccC", ""};
    const std::vector<std::string> split_string4_exp = {"AaaABbbBCccC"};

    ASSERT_STD_VEC_EQ_STD_VEC(split_string0, split_string0_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string1, split_string1_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string2, split_string2_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string3, split_string3_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string4, split_string4_exp);
}

TEST_F(StringUtilsTest, TestSplitStringWithTestVectors)
{
    ASSERT_EQ(test_strings.size(), delimiters.size());
    ASSERT_EQ(gt_vectors.size(), delimiters.size());

    for (size_t k = 0; k < test_strings.size(); k++)
    {
        const std::string delim = delimiters[k];
        const std::string string_to_test = test_strings[k];

        const std::vector<std::string> split_string_act = splitString(string_to_test, delim);
        const std::vector<std::string> split_string_exp = gt_vectors[k];

        ASSERT_STD_VEC_EQ_STD_VEC(split_string_exp, split_string_act);
    }
}

TEST_F(StringUtilsTest, TestSortStringVector)
{
    const std::vector<std::vector<std::string>> v = {
        {"00001", "3", "6", "5", "2", "9", "0", "3", "-001", "3"},
        {"2", "1", "5", "4", "4", "2", "4"},
        {"-1", "-3", "4", "-3", "-3", "2", "-5", "6", "9"}};
    for (size_t k = 0; k < v.size(); k++)
    {
        const auto res = sortIntegerStringVector(v[k]);
        ASSERT_EQ(res.size(), v[k].size());
        for (size_t i = 0; i < (res.size() - 1); i++)
        {
            const int current_num = std::stoi(res[i], nullptr, 10);
            const int next_num = std::stoi(res[i + 1], nullptr, 10);
            ASSERT_GE(next_num, current_num);
        }
    }
}

}  // namespace arl
