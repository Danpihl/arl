#ifndef UTILITIES_MISC_H_
#define UTILITIES_MISC_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "arl/utilities/logging.h"

namespace arl
{
bool fileExists(std::string path);
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
