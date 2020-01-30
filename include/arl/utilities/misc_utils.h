#ifndef UTILITIES_MISC_H_
#define UTILITIES_MISC_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "arl/utilities/logging.h"

namespace arl
{
enum class Month
{
    Jan,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
};

/*std::string monthEnumToString(const Month m)
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
}*/

struct Time
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

std::string getTimeNow();
void printStringLines(std::vector<std::string> string_lines);

template <typename T> void printVectorOfVectors(std::vector<std::vector<T>> data)
{
    for (size_t r = 0; r < data.size(); r++)
    {
        std::vector<T>& data_row = data[r];
        for (size_t c = 0; c < data_row.size(); c++)
        {
            std::cout << data_row[c];
            if (c != (data_row.size() - 1))
            {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }
}

}  // namespace arl

#endif
