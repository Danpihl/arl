#include "arl/utilities/string_utils.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "arl/utilities/logging.h"

namespace arl
{
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
