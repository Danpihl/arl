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

std::vector<std::string> splitString3(const std::string& string_to_split,
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
                if (string_to_split == "f a e r a")
                {
                    PRINT() << "here";
                }
                if (indices[0] == 0)
                {
                    split_string.push_back("");
                }
                else
                {
                    split_string.push_back(string_to_split.substr(0, indices[0]));
                }

                /*
                if indices(1) ~= 1
                    split_string = [split_string, {SubString(s, 1, indices(1) - 1)}];
                else
                    split_string = [split_string, {''}];
                end
                */

                for (size_t k = 0; k < (indices.size() - 1); k++)
                {
                    const size_t idx0 = indices[k];
                    const size_t idx1 = indices[k + 1];
                    split_string.push_back(string_to_split.substr(idx0 + 1, idx1 - idx0 - 1));
                }
                /*
                for k = 1:(length(indices) - 1)
                    idx0 = indices(k);
                    idx1 = indices(k+1);
                    split_string = [split_string, {SubString(s, idx0+1, idx1 - idx0 - 1)}];
                end
                */

                if (indices[indices.size() - 1] == (string_to_split.length() - 1))
                {
                    split_string.push_back("");
                }
                else
                {
                    split_string.push_back(string_to_split.substr(
                        indices[indices.size() - 1] + 1,
                        string_to_split.length() - indices[indices.size() - 1]));
                }

                /*
                if indices(end) ~= length(s)
                    split_string = [split_string, {SubString(s, indices(end) + 1, length(s) -
                indices(end))}]; else split_string = [split_string, {''}]; end
                */
            }
        }
    }

    return split_string;
}

std::vector<std::string> splitString2(const std::string& string_to_split,
                                      const std::string& delimiter)
{
    ASSERT(delimiter.size()) << "Can't have zero size delimiter!";
    std::vector<size_t> indices = findSubStringIndices(string_to_split, delimiter);

    std::vector<std::string> res_vec;

    if (indices.size() == 0)
    {
        res_vec.push_back(string_to_split);
    }
    else if (indices.size() == 1)
    {
        if (indices[0] == 0)
        {
            res_vec.push_back("");
            res_vec.push_back(string_to_split.substr(1, string_to_split.length() - 1));
        }
        else if (indices[0] == (string_to_split.length() - 1))
        {
            res_vec.push_back(string_to_split.substr(0, indices[0]));
            res_vec.push_back("");
        }
        else
        {
            res_vec.push_back(string_to_split.substr(0, indices[0]));
            res_vec.push_back(
                string_to_split.substr(indices[0] + 1, string_to_split.length() - indices[0] - 1));
        }
    }
    else
    {
        // TODO:
        // indices.insert(indices.begin(), 0);
        // indices.push_back(string_to_split.length() - 1);

        if (indices[0] == 0)
        {
            res_vec.push_back("");
        }
        else
        {
            indices.push_back(0);
        }

        for (size_t k = 0; k < (indices.size() - 1); k++)
        {
            const size_t idx0 = indices[k];
            const size_t idx1 = indices[k + 1];
            ASSERT(idx0 != idx1) << "Indices shouldn't be equal! Bug!";
            if ((idx0 + 1) == idx1)
            {
                res_vec.push_back("");
            }
            else
            {
                res_vec.push_back(string_to_split.substr(idx0 + 1, idx1 - idx0 - 1));
            }
        }

        if (*(indices.end() - 1) == (string_to_split.length() - 1))
        {
            res_vec.push_back("");
        }
    }

    return res_vec;
}

std::vector<std::string> splitString(const std::string& string_to_split,
                                     const std::string& delimiter)
{
    std::string copied_string = string_to_split;
    std::vector<std::string> sub_string_vector;

    size_t pos = 0;
    std::string sub_string;
    while ((pos = copied_string.find(delimiter)) != std::string::npos)
    {
        if (pos == 0)
        {
            sub_string = "";
        }
        else
        {
            sub_string = copied_string.substr(0, pos);
        }

        sub_string_vector.push_back(sub_string);
        copied_string.erase(0, pos + delimiter.length());
    }

    if (copied_string.length() != 0)
    {
        sub_string_vector.push_back(copied_string);
    }

    if (string_to_split.substr(string_to_split.length() - delimiter.length(), delimiter.length()) ==
        delimiter)
    {
        sub_string_vector.push_back("");
    }

    return sub_string_vector;
}

std::vector<std::string> sortIntegerStringVector(const std::vector<std::string>& input_vector)
{
    // Sorts a std::vector<std::string> on the form input_vector = {"2", "1", "3", "0", "4"}
    struct list_entry
    {
        std::string num_as_string;
        int num;
    };

    std::vector<list_entry> combined_list(input_vector.size());

    for (size_t k = 0; k < input_vector.size(); k++)
    {
        const std::string& s = input_vector[k];
        int num = std::stoi(s, nullptr, 10);

        list_entry li = {s, num};
        combined_list[k] = li;
    }

    std::sort(combined_list.begin(), combined_list.end(), [](list_entry i, list_entry j) {
        return i.num < j.num;
    });

    std::vector<std::string> sorted_list(input_vector.size());

    for (size_t k = 0; k < combined_list.size(); k++)
    {
        sorted_list[k] = combined_list[k].num_as_string;
    }

    return sorted_list;
}

}  // namespace arl
