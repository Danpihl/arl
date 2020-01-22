#ifndef STRING_TEST_DATA_H_
#define STRING_TEST_DATA_H_

#include <string>
#include <vector>

std::vector<std::string> test_strings = {"",
                                         " ",
                                         "  ",
                                         "   ",
                                         "faera",
                                         "f a e r a",
                                         "f a  er   a",
                                         " f a  er   a ",
                                         "  f a  er   a  ",
                                         "  f a  er    a   ",
                                         "ad",
                                         "ad",
                                         "ad",
                                         "",
                                         "a",
                                         "a",
                                         "ff a e r as",
                                         "faa a  er   afer"};

std::vector<std::vector<std::string>> gt_vectors = {
    {""},
    {"", ""},
    {"", "", ""},
    {"", "", "", ""},
    {"faera"},
    {"f", "a", "e", "r", "a"},
    {"f", "a", "", "er", "", "", "a"},
    {"", "f", "a", "", "er", "", "", "a", ""},
    {"", "", "f", "a", "", "er", "", "", "a", "", ""},
    {"", "", "f", "a", "", "er", "", "", "", "a", "", "", ""},
    {"", ""},
    {"ad"},
    {"ad"},
    {""},
    {"a"},
    {"a"},
    {"ff", "a", "e", "r", "as"},
    {"faa", "a", "", "er", "", "", "afer"}};

std::vector<std::string> delimiters = {
    " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "ad", "adf", "af", "af", "b", "ba", " ", " "};

#endif
