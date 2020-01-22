#ifndef UTILITIES_STRING_UTILS_H_
#define UTILITIES_STRING_UTILS_H_

#include <string>
#include <vector>

namespace arl
{
std::vector<std::string> splitString(const std::string& string_to_split,
                                     const std::string& delimiter);
std::vector<std::string> sortIntegerStringVector(const std::vector<std::string>& input_vector);
std::vector<size_t> findSubStringIndices(const std::string& str, const std::string& sub_str);
std::vector<std::string> splitString2(const std::string& string_to_split,
                                      const std::string& delimiter);
std::vector<std::string> splitString3(const std::string& string_to_split,
                                      const std::string& delimiter);
}  // namespace arl

#endif
