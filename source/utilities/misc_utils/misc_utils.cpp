#include "arl/utilities/misc_utils.h"

#include <sys/time.h>

#include "arl/utilities/logging.h"

namespace arl
{
std::string getTimeNow()
{
    const std::time_t t = std::time(0);
    const std::tm* now = std::localtime(&t);

    const std::string time_year = std::to_string(now->tm_year + 1900);

    const std::string time_month = (now->tm_mon + 1) < 10 ? "0" + std::to_string(now->tm_mon + 1)
                                                          : std::to_string(now->tm_mon + 1);
    const std::string time_day = (now->tm_mday + 1) < 10 ? "0" + std::to_string(now->tm_mday + 1)
                                                         : std::to_string(now->tm_mday + 1);
    const std::string time_hour =
        now->tm_hour < 10 ? "0" + std::to_string(now->tm_hour) : std::to_string(now->tm_hour);
    const std::string time_min =
        now->tm_min < 10 ? "0" + std::to_string(now->tm_min) : std::to_string(now->tm_min);
    const std::string time_seconds =
        now->tm_sec < 10 ? "0" + std::to_string(now->tm_sec) : std::to_string(now->tm_sec);

    return time_year + "_" + time_month + "_" + time_day + "-" + time_hour + "_" + time_min + "_" +
           time_seconds;
}

void printStringLines(std::vector<std::string> string_lines)
{
    for (size_t k = 0; k < string_lines.size(); k++)
    {
        std::cout << string_lines[k];
        if (string_lines[k][string_lines[k].length() - 1] != '\n')
        {
            std::cout << std::endl;
        }
    }
}

}  // namespace arl
