#include "arl/utilities/string_utils.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "arl/utilities/logging.h"

namespace arl
{
std::vector<size_t> findSubStringIndices(const std::string& str, const std::string& sub_str)
{
    ASSERT(sub_str.length() > 0) << "Can not find empty substring!";
    std::vector<size_t> res_vec;

    if (str.size() > 0)
    {
        if (str.length() >= sub_str.length())
        {
            for (size_t k = 0; k < (str.length() + 1 - sub_str.length()); k++)
            {
                const std::string current_sub_str = str.substr(k, sub_str.length());
                if (current_sub_str == sub_str)
                {
                    res_vec.push_back(k);
                }
            }
        }
    }
    return res_vec;
}

std::vector<std::string> splitString(const std::string& string_to_split,
                                     const std::string& delimiter)
{
    ASSERT(delimiter.size()) << "Can't have zero size delimiter!";

    std::vector<std::string> split_string;

    if (string_to_split.length() == 0)
    {
        split_string.push_back("");
    }
    else if (string_to_split.length() == 1)
    {
        if (delimiter.length() > string_to_split.length())
        {
            split_string.push_back(string_to_split);
        }
        else  // Lengths are equal (delimiter can't have length 0)
        {
            if (string_to_split == delimiter)
            {
                split_string.push_back("");
                split_string.push_back("");
            }
            else
            {
                split_string.push_back(string_to_split);
            }
        }
    }
    else
    {
        if (delimiter.length() > string_to_split.length())
        {
            split_string.push_back(string_to_split);
        }
        else if (delimiter.length() == string_to_split.length())
        {
            if (string_to_split == delimiter)
            {
                split_string.push_back("");
                split_string.push_back("");
            }
            else
            {
                split_string.push_back(string_to_split);
            }
        }
        else
        {
            const std::vector<size_t> indices = findSubStringIndices(string_to_split, delimiter);
            if (indices.size() == 0)
            {
                split_string.push_back(string_to_split);
            }
            else
            {
                if (indices[0] == 0)
                {
                    split_string.push_back("");
                }
                else
                {
                    split_string.push_back(string_to_split.substr(0, indices[0]));
                }

                for (size_t k = 0; k < (indices.size() - 1); k++)
                {
                    const size_t idx0 = indices[k] + delimiter.length();
                    const size_t idx1 = indices[k + 1];

                    split_string.push_back(string_to_split.substr(idx0, idx1 - idx0));
                }

                if (indices[indices.size() - 1] == (string_to_split.length() - 1))
                {
                    split_string.push_back("");
                }
                else
                {
                    split_string.push_back(string_to_split.substr(
                        indices[indices.size() - 1] + delimiter.length(),
                        string_to_split.length() - indices[indices.size() - 1]));
                }
            }
        }
    }

    return split_string;
}

std::vector<std::string> sortIntegerStringVector(const std::vector<std::string>& input_vector)
{
    // Sorts a std::vector<std::string> on the form input_vector = {"2", "1", "3", "0", "4"}
    std::vector<std::string> output_vector = input_vector;

    auto predicate_func = [](std::string s0, std::string s1) -> bool {
        const int i0 = std::stoi(s0, nullptr, 10);
        const int i1 = std::stoi(s1, nullptr, 10);
        return i0 < i1;
    };
    std::sort(output_vector.begin(), output_vector.end(), predicate_func);

    return output_vector;
}

}  // namespace arl
