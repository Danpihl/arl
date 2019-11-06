#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "arl/utilities/algorithm.h"
#include "arl/utilities/filesystem.h"
#include "arl/utilities/logging.h"

namespace arl
{
class AlgorithmTest : public testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(AlgorithmTest, TestForEachApplyToStdVec)
{
    auto f = [](std::string& s) { s = s + "hej"; };

    std::vector<std::string> v = {"ja", "ne", "tm"};
    std::vector<std::string> v_original = v;

    forEachApply(v, f);

    for (size_t k = 0; k < v.size(); k++)
    {
        ASSERT_EQ(v[k], v_original[k] + "hej");
    }
}

TEST_F(AlgorithmTest, TestForEachApplyToArlVec)
{
    auto f = [](std::string& s) { s = s + "hej"; };

    Vector<std::string> v = {"ja", "ne", "tm"};
    Vector<std::string> v_original = v;

    forEachApply(v, f);

    for (size_t k = 0; k < v.size(); k++)
    {
        ASSERT_EQ(v(k), v_original(k) + "hej");
    }
}

TEST_F(AlgorithmTest, TestForEachApplyToNewStdVector)
{
    auto f = [](const std::string& s) -> std::string { return s + "hej"; };

    const std::vector<std::string> v = {"ja", "ne", "tm"};

    const std::vector<std::string> v_res = forEachApplyToNewVec(v, f);

    for (size_t k = 0; k < v.size(); k++)
    {
        ASSERT_EQ(v_res[k], v[k] + "hej");
    }
}

TEST_F(AlgorithmTest, TestForEachApplyToNewArlVector)
{
    auto f = [](const std::string& s) -> std::string { return s + "hej"; };

    const Vector<std::string> v = {"ja", "ne", "tm"};

    const Vector<std::string> v_res = forEachApplyToNewVec(v, f);

    for (size_t k = 0; k < v.size(); k++)
    {
        ASSERT_EQ(v_res(k), v(k) + "hej");
    }
}

}  // namespace arl
