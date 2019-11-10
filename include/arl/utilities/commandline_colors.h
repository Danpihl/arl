#ifndef UTILITIES_COMMANDLINE_COLORS_H_
#define UTILITIES_COMMANDLINE_COLORS_H_

#include <string>
#include <vector>

namespace arl
{
enum class CommandColorString
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

std::string resetColorString();
std::string stringCol(const CommandColorString background_color,
                      const CommandColorString foreground_color);

}  // namespace arl

#endif
