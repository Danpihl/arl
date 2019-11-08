#ifndef UTILITIES_CSV_UTILITIES_H_
#define UTILITIES_CSV_UTILITIES_H_

#include <string>
#include <vector>

namespace arl
{
void writeIntCsvFile(const std::string &output_folder,
                     const std::string &output_file_name,
                     const std::vector<std::vector<int>> &data);
std::vector<std::vector<int>> readIntCsvFile(const std::string &folder_path,
                                             const std::string &file_name);

void writeDoubleCsvFile(const std::string &output_folder,
                        const std::string &output_file_name,
                        const std::vector<std::vector<double>> &data);
std::vector<std::vector<double>> readDoubleCsvFile(const std::string &folder_path,
                                                   const std::string &file_name);

void writeStringCsvFile(const std::string &output_folder,
                        const std::string &output_file_name,
                        const std::vector<std::vector<std::string>> &data);
std::vector<std::vector<std::string>> readStringCsvFile(const std::string &folder_path,
                                                        const std::string &file_name);

} // namespace arl

#endif
