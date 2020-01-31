#include "arl/utilities/misc_utils.h"

#include <sys/time.h>

#include "arl/utilities/logging.h"

namespace arl
{
std::string Time::toString() const
{
    const std::string time_year = std::to_string(year);

    const std::string time_month = month < 10 ? "0" + std::to_string(month) : std::to_string(month);
    const std::string time_day = day < 10 ? "0" + std::to_string(day) : std::to_string(day);
    const std::string time_hour = hour < 10 ? "0" + std::to_string(hour) : std::to_string(hour);
    const std::string time_min =
        minute < 10 ? "0" + std::to_string(minute) : std::to_string(minute);
    const std::string time_seconds =
        second < 10 ? "0" + std::to_string(second) : std::to_string(second);

    return time_year + "_" + time_month + "_" + time_day + "-" + time_hour + "_" + time_min + "_" +
           time_seconds;
}

Time getTimeNow()
{
    const std::time_t t = std::time(0);
    const std::tm* now = std::localtime(&t);

    Time time_now;

    time_now.year = now->tm_year + 1900;

    time_now.month = now->tm_mon + 1;
    time_now.day = now->tm_mday;
    time_now.hour = now->tm_hour;
    time_now.minute = now->tm_min;
    time_now.second = now->tm_sec;

    return time_now;
}

std::string monthEnumToString(const Month m)
{
    std::string s;
    switch (m)
    {
        case Month::Jan:
            s = "Jan";
            break;
        case Month::Feb:
            s = "Feb";
            break;
        case Month::Mar:
            s = "Mar";
            break;
        case Month::Apr:
            s = "Apr";
            break;
        case Month::May:
            s = "May";
            break;
        case Month::Jun:
            s = "Jun";
            break;
        case Month::Jul:
            s = "Jul";
            break;
        case Month::Aug:
            s = "Aug";
            break;
        case Month::Sep:
            s = "Sep";
            break;
        case Month::Oct:
            s = "Oct";
            break;
        case Month::Nov:
            s = "Nov";
            break;
        case Month::Dec:
            s = "Dec";
            break;
        default:
            EXIT() << "Invalid month!";
            break;
    }

    return s;
}

void printStringLines(const std::vector<std::string>& string_lines)
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
