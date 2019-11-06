#ifndef DATA_LOGGER_H_
#define DATA_LOGGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <cassert>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <arl/utilities/logging.h>

// TODO: Add global namespace and internal namespace

// TODO: Make name obscure:
#define nameOfType(x) #x

/* Usage
dumpData<int>("file_controller", "ux", ux);
dumpData<int>("file_controller", "uy", uy);
dumpData<double>("file_filter", "Vx", Vx);
*/

inline std::string getTimeNowInternal()
{
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);

    const auto g = [](const int i) -> std::string {
        if (i < 10)
        {
            return "0" + std::to_string(i);
        }
        else
        {
            return std::to_string(i);
        }
    };

    const std::string time_string = g(timeinfo->tm_year + 1900) + "_" + g(timeinfo->tm_mon + 1) +
                                    "_" + g(timeinfo->tm_mday) + ":" + g(timeinfo->tm_hour) + "_" +
                                    g(timeinfo->tm_min) + "_" + g(timeinfo->tm_sec);

    return time_string;
}

inline bool isStringType(const std::string& s)
{
    return s.find("string") != std::string::npos;
}

// TODO: Possibly not portable, might have different results with different compilers
inline std::string extractTypeFromTemplateType(const char* raw_str)
{
    const std::string s(raw_str);

    const size_t type_start_pos = s.find("T = ") + std::string("T = ").length();
    const std::string type_str =
        std::string(s.begin() + type_start_pos, s.begin() + s.length() - 1);

    if (type_str.find("::vector") != std::string::npos)
    {
        // Is of type vector
        const size_t vector_string_pos =
            type_str.find("::vector<") + std::string("::vector<").length();

        const std::string type_str_no_vector =
            std::string(type_str.begin() + vector_string_pos, type_str.begin() + type_str.length());
        const size_t comma_idx = type_str_no_vector.find(',');

        const std::string new_string = type_str_no_vector.substr(0, comma_idx);

        if (isStringType(new_string))
        {
            return "vector<string>";
        }
        else
        {
            return "vector<" + new_string + ">";
        }
    }
    else
    {
        if (type_str.find('*') != std::string::npos)
        {
            const size_t asterisk_idx = type_str.find('*');
            return type_str.substr(0, asterisk_idx - 1) + "*";
        }
        else
        {
            if (isStringType(type_str))
            {
                return "string";
            }
            else
            {
                return type_str;
            }
        }
    }
}

// **************************************************************
// ************************** Variable **************************
// **************************************************************

class Variable
{
private:
    size_t num_elements;
    std::vector<char> data;

public:
    const std::string name;
    const unsigned char name_length;

    const std::string type_name;
    const unsigned char type_name_length;

    const char num_bytes_per_element;

    Variable();
    Variable(const std::string& name_,
             const std::string& type_name_,
             const size_t num_bytes_per_element_);

    template <typename T> void addSingleElement(const T element);
    void addMultipleElements(const void* element_array, const size_t num_new_elements);

    void setNumElements(size_t new_val);
    size_t getNumElements() const;

    const char* getDataVectorPointer() const;

    std::string headerDataToString() const;
};

template <typename T> void Variable::addSingleElement(const T element)
{
    assert(static_cast<size_t>(num_bytes_per_element) == sizeof(T));
    const char* data_ptr = reinterpret_cast<const char*>(&element);

    for (size_t k = 0; k < sizeof(T); k++)
    {
        data.push_back(data_ptr[k]);
    }
    num_elements++;
}

inline void Variable::addMultipleElements(const void* element_array, const size_t num_new_elements)
{
    const char* data_ptr = reinterpret_cast<const char*>(element_array);

    for (size_t k = 0; k < (num_new_elements * static_cast<size_t>(num_bytes_per_element)); k++)
    {
        data.push_back(data_ptr[k]);
    }
    num_elements = num_elements + num_new_elements;
}

inline std::string Variable::headerDataToString() const
{
    std::string res_string = "";
    res_string.push_back(name_length);
    res_string = res_string + name;

    res_string.push_back(type_name_length);
    res_string = res_string + type_name;

    res_string.push_back(num_bytes_per_element);

    const char* data_ptr = reinterpret_cast<const char*>(&num_elements);
    for (size_t k = 0; k < sizeof(size_t); k++)
    {
        res_string.push_back(data_ptr[k]);
    }

    return res_string;
}

inline Variable::Variable()
    : num_elements(0),
      name(""),
      name_length(0),
      type_name(""),
      type_name_length(0),
      num_bytes_per_element(0)
{
}

inline Variable::Variable(const std::string& name_,
                          const std::string& type_name_,
                          const size_t num_bytes_per_element_)
    : num_elements(0),
      name(name_),
      name_length(name_.length()),
      type_name(type_name_),
      type_name_length(type_name_.length()),
      num_bytes_per_element(static_cast<char>(num_bytes_per_element_))
{
    assert(name_.length() <= 256);
    assert(type_name_.length() <= 256);
}

inline const char* Variable::getDataVectorPointer() const
{
    assert((data.size() > 0) && "Vector not allocated yet!");
    return data.data();
}

inline void Variable::setNumElements(size_t new_val)
{
    num_elements = new_val;
}

inline size_t Variable::getNumElements() const
{
    return num_elements;
}

template <typename T> Variable createVariable(const std::string& name)
{
    return Variable(name, extractTypeFromTemplateType(__PRETTY_FUNCTION__), sizeof(T));
}

// *************************************************************************
// ************************** GenericBinaryLogger **************************
// *************************************************************************

class GenericBinaryLogger
{
private:
    bool files_are_open_;
    bool use_time_in_file_name_;

    void clearMap();

public:
    std::map<std::string, std::map<std::string, Variable>> data;

    GenericBinaryLogger();
    ~GenericBinaryLogger();

    void setUseTimeInFileName(const bool use_time_in_file_name);

    void newFile(const std::string& file_name);
    template <typename T> void newVar(const std::string& file_name, const std::string& var_name);

    bool hasFile(const std::string& file_name) const;
    bool fileHasVariable(const std::string& file_name, const std::string& var_name) const;

    std::vector<std::string> getFileNames() const;
    std::vector<std::string> getVariablesInFile(const std::string& file_name) const;

    void close();
};

inline GenericBinaryLogger::GenericBinaryLogger()
    : files_are_open_(true), use_time_in_file_name_(false)
{
}

inline GenericBinaryLogger::~GenericBinaryLogger()
{
    close();
}

inline void GenericBinaryLogger::clearMap()
{
    for (auto& file_key_val_pair : data)
    {
        const std::string file_name = file_key_val_pair.first;
        file_key_val_pair.second.clear();
    }
    data.clear();
}

class ReadFile
{
private:
public:
    ReadFile() = default;
    ReadFile(const std::string& file_name);
};

/*inline ReadFile::ReadFile(const std::string &file_name)
{
    ReadFile read_file;

    FILE* file_handle = fopen(file_name.c_str(), "rb");
    if (!file_handle)
    {
        std::cout << "File " << file_name << " failed to open!" << std::endl;
        exit(-1);
    }
    else
    {
        read_file.file_size = fileSize(file_name);
        if (read_file.file_size == 0)
        {
            read_file.buffer = nullptr;
            LOG_INFO() << "Read file " << file_name << " is empty!";
        }
        else
        {
            read_file.buffer = new char[read_file.file_size];
            fread(read_file.buffer, read_file.file_size, 1, file_handle);
        }
        fclose(file_handle);
    }
    return read_file;
}*/

// TODO: Create function that reads binary file
// Write to file is essentially done, but not tested

inline void saveToFile(const std::string& file_name, const std::map<std::string, Variable>& var_map)
{
    FILE* file_handle = fopen(file_name.c_str(), "wb");

    if (!file_handle)
    {
        std::cout << "File not open!" << std::endl;
        exit(-1);
    }

    const char num_vars = var_map.size();

    fwrite(&num_vars, 1, 1, file_handle);

    std::string header_string;

    for (const std::pair<std::string, Variable>& m : var_map)
    {
        header_string = header_string + m.second.headerDataToString();
    }

    fwrite(header_string.c_str(), 1, header_string.length(), file_handle);

    for (const std::pair<std::string, Variable>& m : var_map)
    {
        const std::string var_name = m.first;
        const Variable var = m.second;
        const char* data_ptr = var.getDataVectorPointer();

        const size_t num_bytes_per_element = var.num_bytes_per_element;

        const size_t total_num_bytes = num_bytes_per_element * var.getNumElements();

        fwrite(data_ptr, 1, total_num_bytes, file_handle);
    }
    fclose(file_handle);
}

inline void GenericBinaryLogger::close()
{
    if (files_are_open_)
    {
        files_are_open_ = false;

        for (const auto& file_key_val_pair : data)
        {
            const std::string file_name = file_key_val_pair.first;

            saveToFile(file_name, file_key_val_pair.second);

            /*for (const auto& var_key_value_pair : data[file_name])
            {
                const std::string var_name = var_key_value_pair.first;
                // PRINT() << var_name;

                const Variable var = var_key_value_pair.second;
                const char* data_ptr = var.getDataVectorPointer();
                const size_t num_bytes_per_element = var.num_bytes_per_element;

                for (size_t k = 0; k < (num_bytes_per_element * var.getNumElements()); k++)
                {
                    // PRINT() << static_cast<int>(data_ptr[k]);
                }
                //
            }*/
        }
        // PRINT() << "Closed";
        // Dump all data to file
    }
    clearMap();
}

inline void GenericBinaryLogger::setUseTimeInFileName(const bool use_time_in_file_name)
{
    use_time_in_file_name_ = use_time_in_file_name;
}

inline bool GenericBinaryLogger::fileHasVariable(const std::string& file_name,
                                                 const std::string& var_name) const
{
    if (!hasFile(file_name))
    {
        return false;
    }
    else
    {
        return data.at(file_name).count(var_name) > 0;
    }
}

inline bool GenericBinaryLogger::hasFile(const std::string& file_name) const
{
    return data.count(file_name) > 0;
}

inline void GenericBinaryLogger::newFile(const std::string& file_name)
{
    assert(!hasFile(file_name) && "Tried to add file that already exists!");

    data.insert({file_name, std::map<std::string, Variable>()});
}

template <typename T>
void GenericBinaryLogger::newVar(const std::string& file_name, const std::string& var_name)
{
    assert(hasFile(file_name) && "Tried to create variable in non existing file!");
    assert(!fileHasVariable(file_name, var_name) &&
           "Tried to add variable that already exists for file!");

    data[file_name].insert({var_name, createVariable<T>(var_name)});
}

inline std::vector<std::string> GenericBinaryLogger::getFileNames() const
{
    std::vector<std::string> res_vec;
    for (const auto& key_val_pair : data)
    {
        res_vec.push_back(key_val_pair.first);
    }
    return res_vec;
}

inline std::vector<std::string> GenericBinaryLogger::getVariablesInFile(
    const std::string& file_name) const
{
    if (!hasFile(file_name))
    {
        return std::vector<std::string>();
    }
    {
        std::vector<std::string> res_vec;
        for (const auto& key_val_pair : data.at(file_name))
        {
            res_vec.push_back(key_val_pair.first);
        }
        return res_vec;
    }
}

// *************************************************************************
// ************************** Non class functions **************************
// *************************************************************************

inline std::mutex& Var_mutex()
{
    static std::mutex mtx;
    return mtx;
}

inline bool& Var_shouldExit()
{
    static bool should_exit;
    return should_exit;
}

inline GenericBinaryLogger& Var_classInstance()
{
    static GenericBinaryLogger logger_struct;
    return logger_struct;
}

inline bool& Var_isInitialized()
{
    static bool is_initialized = false;
    return is_initialized;
}

inline void signalHandler(int sig)
{
    (void)sig;

    if (Var_mutex().try_lock())
    {
        Var_classInstance().close();
        exit(0);
    }
    else
    {
        Var_shouldExit() = true;
    }
}

template <typename T>
void dumpData(const std::string& file_name, const std::string& var_name, const T var)
{
    const std::lock_guard<std::mutex> lock(Var_mutex());

    // --------------------- Dump data begin ---------------------

    (void)file_name;
    (void)var_name;
    (void)var;

    if (!Var_classInstance().hasFile(file_name))
    {
        Var_classInstance().newFile(file_name);
        Var_classInstance().newVar<T>(file_name, var_name);
    }
    else if (!Var_classInstance().fileHasVariable(file_name, var_name))
    {
        Var_classInstance().newVar<T>(file_name, var_name);
    }

    // TODO: Turn into function:
    Var_classInstance().data[file_name][var_name].addSingleElement(var);

    // ---------------------- Dump data end ----------------------

    if (Var_shouldExit())
    {
        Var_classInstance().close();
        exit(0);
    }
}

inline void deInitDataLogging()
{
    Var_classInstance().close();
    Var_isInitialized() = false;
}

inline void initDataLogging()
{
    if (!Var_isInitialized())
    {
        Var_isInitialized() = true;
        Var_shouldExit() = false;
        Var_classInstance();
        signal(SIGINT, signalHandler);
    }
}

#endif
