#ifndef JSON_FILE_H_
#define JSON_FILE_H_

#include <algorithm>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "arl/utilities/logging.h"

// http://techgate.fr/boost-property-tree/

namespace arl
{

using namespace logging;

class JsonWriter
{
private:
    boost::property_tree::ptree json_file_;
    std::string file_path_;

public:
    JsonWriter(const std::string &file_path);
    void closeFile();
    template <typename T>
    void write(const std::string &key, const T &value);
};

JsonWriter::JsonWriter(const std::string &file_path)
{
    file_path_ = file_path;
}

template <typename T>
void JsonWriter::write(const std::string &key, const T &value)
{
    json_file_.put(key, value);
}

void JsonWriter::closeFile()
{
    boost::property_tree::write_json(file_path_, json_file_);
}

// ------------

class JsonReader
{
private:
    boost::property_tree::ptree json_file_;
    std::string file_path_;

public:
    template <typename T>
    T getKeyValue(const std::string &key_name);
    template <typename T>
    std::vector<T> getVector(const std::string &key_name);
    JsonReader(const std::string &file_path);
};

JsonReader::JsonReader(const std::string &file_path)
{
    file_path_ = file_path;
    boost::property_tree::read_json(file_path, json_file_);
}

template <typename T>
T JsonReader::getKeyValue(const std::string &key_name)
{
    T value;
    try
    {
        value = json_file_.get<T>(key_name);
    }
    catch (boost::exception_detail::clone_impl<
           boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path>> &ex)
    {
        EXIT() << "Couldn't find key \"" << key_name << "\" in json file";
    }

    return value;
}

template <typename T>
std::vector<T> JsonReader::getVector(const std::string &key_name)
{
    std::vector<T> vector_of_values;
    try
    {
        for (const auto &item : json_file_.get_child(key_name.c_str()))
        {
            vector_of_values.push_back(item.second.get_value<T>());
        }
    }
    catch (boost::exception_detail::clone_impl<
           boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path>> &ex)
    {
        EXIT() << "Couldn't find key \"" << key_name << "\" in json file";
    }

    return vector_of_values;
}

// ---------------------------------------------------

template <typename T>
T getJsonKeyValue(const boost::property_tree::ptree &json_file, const std::string &key_name)
{
    T value;
    try
    {
        value = json_file.get<T>(key_name);
    }
    catch (boost::exception_detail::clone_impl<
           boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path>> &ex)
    {
        EXIT() << "Couldn't find key \"" << key_name << "\" in json file";
    }

    return value;
}

template <typename T>
std::vector<T> getJsonList(const boost::property_tree::ptree &json_file,
                           const std::string &key_name)
{
    std::vector<T> vector_of_values;
    try
    {
        for (const auto &item : json_file.get_child(key_name.c_str()))
        {
            vector_of_values.push_back(item.second.get_value<T>());
        }
    }
    catch (boost::exception_detail::clone_impl<
           boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path>> &ex)
    {
        EXIT() << "Couldn't find key \"" << key_name << "\" in json file";
    }

    return vector_of_values;
}

template <typename T>
T getJsonKeyValueFromJsonFile(const std::string &json_file_path, const std::string &key_name)
{
    boost::property_tree::ptree json_file;
    boost::property_tree::read_json(json_file_path, json_file);

    T value;
    try
    {
        value = json_file.get<T>(key_name);
    }
    catch (boost::exception_detail::clone_impl<
           boost::exception_detail::error_info_injector<boost::property_tree::ptree_bad_path>> &ex)
    {
        EXIT() << "Couldn't find key \"" << key_name << "\" in json file";
    }

    return value;
}

} // namespace arl

#endif
