#include "arl/utilities/misc_utils.h"

#include <sys/time.h>

#include <boost/filesystem.hpp>

#include "arl/utilities/logging.h"

namespace arl
{

std::string getTimeNow()
{
    const std::time_t t = std::time(0);
    const std::tm *now = std::localtime(&t);

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

bool fileExists(std::string path)
{
    return boost::filesystem::exists(path);
}

std::vector<std::string> getFileListFromDir(std::string dir)
{
    ASSERT(fileExists(dir)) << "Couldn't find directory!";

    std::vector<std::string> file_list;

    if (!dir.empty())
    {
        boost::filesystem::path boost_path(dir);
        boost::filesystem::recursive_directory_iterator end_iterator;

        for (boost::filesystem::recursive_directory_iterator it(boost_path); it != end_iterator;
             ++it)
        {
            const boost::filesystem::path file_path = (*it);
            file_list.push_back(file_path.string());
        }
    }

    return file_list;
}

std::vector<std::string> getSortedFileListFromDir(std::string dir)
{
    std::vector<std::string> file_list;

    if (!dir.empty())
    {
        struct list_entry
        {
            std::string name;
            int num;
        };

        std::vector<list_entry> combined_list;
        boost::filesystem::path boost_path(dir);
        boost::filesystem::recursive_directory_iterator end_iterator;

        for (boost::filesystem::recursive_directory_iterator it(boost_path); it != end_iterator;
             ++it)
        {
            const boost::filesystem::path file_path = (*it);

            std::string file_name = file_path.filename().string();
            int num = std::stoi(file_name, nullptr, 10);

            list_entry li = {file_path.string(), num};

            combined_list.push_back(li);
        }

        std::sort(combined_list.begin(), combined_list.end(), [](list_entry i, list_entry j) {
            return i.num < j.num;
        });

        for (auto le : combined_list)
        {
            file_list.push_back(le.name);
        }
    }

    return file_list;
}

std::vector<std::string> getSortedFileListFromDirWithZeroPaddedFiles(std::string dir)
{
    std::vector<std::string> file_list;

    if (!dir.empty())
    {
        boost::filesystem::path boost_path(dir);
        boost::filesystem::recursive_directory_iterator end_iterator;

        for (boost::filesystem::recursive_directory_iterator it(boost_path); it != end_iterator;
             ++it)
        {
            const boost::filesystem::path file_path = (*it);
            file_list.push_back(file_path.string());
        }

        std::sort(file_list.begin(), file_list.end());
    }

    return file_list;
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

} // namespace arl
