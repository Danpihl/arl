#include "arl/utilities/string_utils.h"

#include <iostream>
#include <string>
#include <algorithm>

#include "arl/utilities/logging.h"

namespace arl
{
namespace
{

int stringColorEnumToIntegerValue(const StringColor str_col)
{
    int ret_val;
    switch (str_col)
    {
    case StringColor::BLACK:
        ret_val = 0;
        break;
    case StringColor::RED:
        ret_val = 1;
        break;
    case StringColor::GREEN:
        ret_val = 2;
        break;
    case StringColor::YELLOW:
        ret_val = 3;
        break;
    case StringColor::BLUE:
        ret_val = 4;
        break;
    case StringColor::MAGENTA:
        ret_val = 5;
        break;
    case StringColor::CYAN:
        ret_val = 6;
        break;
    case StringColor::WHITE:
        ret_val = 7;
        break;
    default:
        ret_val = 7;
        break;
    }
    return ret_val;
}

} // namespace

std::string stringCol(const StringColor background_color, const StringColor foreground_color)
{
    int bg_integer = stringColorEnumToIntegerValue(background_color);
    int fg_integer = stringColorEnumToIntegerValue(foreground_color);

    std::string ret_string = "\033[" + std::to_string(bg_integer + 40) + "m" + "\033[" +
                             std::to_string(fg_integer + 30) + "m";
    return ret_string;
}

std::string resetStringCol()
{
    return "\033[0m";
}

std::string joinPaths(const std::string &file_path0, const std::string &file_path1)
{
    ASSERT(file_path0.length() > 0) << "file_path0 was empty!";
    ASSERT(file_path1.length() > 0) << "file_path1 was empty!";

    std::string joined_path =
        file_path0[file_path0.length() - 1] == '/' ? file_path0 : file_path0 + "/";
    joined_path = joined_path + file_path1;

    return joined_path;
}

std::string extractFileNameFromPath(const std::string &file_path)
{
    const int idx = file_path.find_last_of("/");
    const int total_length = file_path.length();
    return file_path.substr(idx + 1, total_length - idx - 1);
}

std::string extractPathFromFullFilePath(const std::string &full_file_path)
{
    // TODO: What happens if this is already a folder path?
    const int idx = full_file_path.find_last_of("/");
    return full_file_path.substr(0, idx);
}

std::vector<std::string> splitString(const std::string &string_to_split,
                                     const std::string &delimiter)
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

std::vector<std::string> sortIntegerStringVector(const std::vector<std::string> &input_vector)
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
        const std::string &s = input_vector[k];
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

} // namespace arl
