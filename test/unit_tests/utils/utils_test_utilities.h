#ifndef UTILS_TEST_UTILITIES_H_
#define UTILS_TEST_UTILITIES_H_

#include <gtest/gtest.h>
#include <iostream>
#include <string>

void printStringVecForSplitStringDebug(const std::vector<std::string>& v)
{
    size_t idx = 0;
    for (const std::string s : v)
    {
        std::cout << idx << ":";
        idx++;
        if (s == "")
        {
            std::cout << "<empty>" << std::endl;
        }
        else
        {
            std::cout << s << "|" << std::endl;
        }
    }
    std::cout << std::endl;
}

void printStringVec(const std::vector<std::string>& v)
{
    for (const std::string s : v)
    {
        std::cout << s << std::endl;
    }
    std::cout << std::endl;
}

#define ASSERT_STD_VEC_EQ_STD_VEC(v0, v1)      \
    {                                          \
        ASSERT_EQ(v0.size(), v1.size());       \
        for (size_t k = 0; k < v0.size(); k++) \
        {                                      \
            ASSERT_EQ(v0[k], v1[k]);           \
        }                                      \
    }

#endif
