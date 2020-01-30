#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "arl/math/math.h"
#include "arl/utilities/logging.h"
#include "arl/utilities/textfile_utils.h"

int main()
{
    std::vector<std::string> lines_to_write = {"hejsan"};
    lines_to_write.push_back("vad heter");
    lines_to_write.push_back("    duuuuu   ");
    lines_to_write.push_back("vaaa");
    lines_to_write.push_back("heh");
    arl::writeTextFileLines(
        lines_to_write, "/Users/danielpihlquist/programming_projects/arl/build", "test_File.txt");

    std::vector<std::string> read_lines = arl::readTextFileLines(
        "/Users/danielpihlquist/programming_projects/arl/build", "test_File.txt");

    for (size_t k = 0; k < read_lines.size(); k++)
    {
        PRINT() << read_lines[k];
    }

    return 0;
}
