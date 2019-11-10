#include "arl/utilities/filesystem_utils.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "arl/utilities/logging.h"
namespace arl
{
namespace
{
int CommandColorStringEnumToIntegerValue(const CommandColorString str_col)
{
    int ret_val;
    switch (str_col)
    {
        case CommandColorString::BLACK:
            ret_val = 0;
            break;
        case CommandColorString::RED:
            ret_val = 1;
            break;
        case CommandColorString::GREEN:
            ret_val = 2;
            break;
        case CommandColorString::YELLOW:
            ret_val = 3;
            break;
        case CommandColorString::BLUE:
            ret_val = 4;
            break;
        case CommandColorString::MAGENTA:
            ret_val = 5;
            break;
        case CommandColorString::CYAN:
            ret_val = 6;
            break;
        case CommandColorString::WHITE:
            ret_val = 7;
            break;
        default:
            ret_val = 7;
            break;
    }
    return ret_val;
}

}  // namespace

std::string stringCol(const CommandColorString background_color,
                      const CommandColorString foreground_color)
{
    int bg_integer = CommandColorStringEnumToIntegerValue(background_color);
    int fg_integer = CommandColorStringEnumToIntegerValue(foreground_color);

    std::string ret_string = "\033[" + std::to_string(bg_integer + 40) + "m" + "\033[" +
                             std::to_string(fg_integer + 30) + "m";
    return ret_string;
}

std::string resetColorString()
{
    return "\033[0m";
}

}  // namespace arl
