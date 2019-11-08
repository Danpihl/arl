#ifndef UTILITIES_STRING_UTILS_H_
#define UTILITIES_STRING_UTILS_H_

#include <string>
#include <vector>

namespace arl
{
enum class StringColor
{
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

std::string stringCol(StringColor background_color, StringColor foreground_color);
std::string resetStringCol();
std::string joinPaths(const std::string &file_path0, const std::string &file_path1);
std::string extractFileNameFromPath(const std::string &file_path);
std::string extractPathFromFullFilePath(const std::string &full_file_path);
std::vector<std::string> splitString(const std::string &string_to_split,
                                     const std::string &delimiter);
std::vector<std::string> sortIntegerStringVector(const std::vector<std::string> &input_vector);

} // namespace arl

#endif
