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

    /*for (size_t k = 0; k < split_str_exp.size(); k++)
    {
        // ASSERT_EQ(split_str_exp[k], split_str_act[k]);
        std::cout << split_str_act[k] << std::endl;
    }*/
}

TEST_F(StringUtilsTest, TestFindSubStringIndices)
{
    const std::string s0 = "micdfacdeorcdmmacdfcdcdoacd";
    const std::string sub_str = "cd";
    std::vector<size_t> indices = findSubStringIndices(s0, sub_str);
    for (size_t k = 0; k < indices.size(); k++)
    {
        // PRINT() << indices[k];
    }
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
    const std::vector<std::string> split_string0 = splitString2(s0, delim);
    const std::vector<std::string> split_string1 = splitString2(s1, delim);
    const std::vector<std::string> split_string2 = splitString2(s2, delim);
    const std::vector<std::string> split_string3 = splitString2(s3, delim);
    const std::vector<std::string> split_string4 = splitString2(s4, delim);

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

TEST_F(StringUtilsTest, TestSplitStringMultipleSpaces)
{
    const std::string delim = " ";

    const std::string s0 = "  AaaA  B bb   B Cc cC ";
    const std::string s1 = "     ";
    const std::string s2 = "          ";
    const std::string s3 = " d  d  ";
    const std::string s4 = "  dd   d dd  d ";
    const std::string s5 = "d     d ";
    const std::string s6 = " d     d";
    const std::string s7 = "d     d  ";
    const std::string s8 = "  d     d";
    const std::string s9 = " ";

    const std::vector<std::string> split_string0 = splitString3(s0, delim);
    const std::vector<std::string> split_string1 = splitString3(s1, delim);
    const std::vector<std::string> split_string2 = splitString3(s2, delim);
    const std::vector<std::string> split_string3 = splitString3(s3, delim);
    const std::vector<std::string> split_string4 = splitString3(s4, delim);
    const std::vector<std::string> split_string5 = splitString3(s5, delim);
    const std::vector<std::string> split_string6 = splitString3(s6, delim);
    const std::vector<std::string> split_string7 = splitString3(s7, delim);
    const std::vector<std::string> split_string8 = splitString3(s8, delim);

    const std::vector<std::string> split_string0_exp = {
        "", "", "AaaA", "", "B", "bb", "", "", "B", "Cc", "cC", ""};
    const std::vector<std::string> split_string1_exp = {"", "", "", "", "", ""};
    const std::vector<std::string> split_string2_exp = {"", "", "", "", "", "", "", "", "", "", ""};
    const std::vector<std::string> split_string3_exp = {"", "d", "", "d", "", ""};
    const std::vector<std::string> split_string4_exp = {
        "", "", "dd", "", "", "d", "dd", "", "d", ""};
    const std::vector<std::string> split_string5_exp = {"d", "", "", "", "", "d", ""};
    const std::vector<std::string> split_string6_exp = {"", "d", "", "", "", "", "d"};
    const std::vector<std::string> split_string7_exp = {"d", "", "", "", "", "d", "", ""};
    const std::vector<std::string> split_string8_exp = {"", "", "d", "", "", "", "", "d"};

    ASSERT_STD_VEC_EQ_STD_VEC(split_string0, split_string0_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string1, split_string1_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string2, split_string2_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string3, split_string3_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string4, split_string4_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string5, split_string5_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string6, split_string6_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string7, split_string7_exp);
    ASSERT_STD_VEC_EQ_STD_VEC(split_string8, split_string8_exp);
}

TEST_F(StringUtilsTest, TestSplitStringWithTestVectors)
{
    ASSERT_EQ(test_strings.size(), delimiters.size());
    ASSERT_EQ(gt_vectors.size(), delimiters.size());

    for (size_t k = 0; k < test_strings.size(); k++)
    {
        const std::string delim = delimiters[k];
        const std::string string_to_test = test_strings[k];
        const std::vector<std::string> split_string_act = splitString3(string_to_test, delim);
        const std::vector<std::string> split_string_exp = gt_vectors[k];
        ASSERT_STD_VEC_EQ_STD_VEC(split_string_exp, split_string_act);
    }
}

}  // namespace arl
