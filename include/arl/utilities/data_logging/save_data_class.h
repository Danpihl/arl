#ifndef BINARY_DUMP_H_
#define BINARY_DUMP_H_

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

/*
Usage:
Declared once in a function call
BinaryDump bd("test file", use_time_now_for_file_name);
bd.dumpPlainOldData<int>(23);
*/

class BinaryDump
{
private:
    bool is_open_;
    size_t num_vars = 0;  // Put in the beginning of file, increment at every dump call, if new var
    // File file;

    std::vector<char> data_to_dump;
    std::vector<std::string> data_to_dump;

    bool hasVariable(const std::string& var) const;

public:
    BinaryDump();
    BinaryDump(const std::string& file_name);

    ~BinaryDump();
    void close();

    template <typename T> void dumpPlainOldData(const T data, const std::string data_name);
    // template <typename T> void dumpPointerData(const T* data, const size_t num_elements, const
    // std::string data_name);
};



/*template <typename T> void BinaryDump::dumpData(const T& data, const std::string data_name)
{
    // "T" must implement "serializeThis()"
}

template <typename T> void BinaryDump::dumpPlainOldDataArray(const T* data, const size_t
num_elements, const std::string data_name)
{

}

template <typename T> void BinaryDump::dumpPlainOldDataVector(const std::vector<T>& data, const
std::string data_name)
{

}*/

// Structure of binary data:
// length of name: 1 byte
// name (in ordinary ascii): a set of bytes with length defined previously
// length of data in bytes: 8 bytes (size_t)
// data: binary data
// Also datatype in string?

template <typename T> void BinaryDump::dumpPlainOldData(const T data, const std::string data_name)
{
    assert((data_name.length() < static_cast<size_t>(256)) && "Name too long!");
    data_to_dump.push_back(data_name.length());

    for (size_t k = 0; k < data_name.length(); k++)
    {
        // file.write(data_name[k]);
        data_to_dump.push_back(data_name[k]);
    }

    const char* data_ptr = reinterpret_cast<const char*>(&data);
    for (size_t k = 0; k < sizeof(T); k++)
    {
        // file.write(data_ptr[k]);
    }
}

BinaryDump::BinaryDump() : is_open_(false) {}

BinaryDump::BinaryDump(const std::string& file_name) : is_open_(true)
{
    // Have number of variables in file name?
    // file.open(file_name);
    // Open binary file
}

BinaryDump::~BinaryDump()
{
    if (is_open_)
    {
        for (size_t k = 0; k < data_to_dump.size(); k++)
        {
            std::cout << static_cast<int>(data_to_dump[k]);
        }
        std::cout << std::endl;
        // Close file
    }
}
void BinaryDump::close()
{
    if (is_open_)
    {
        // Close file
    }
}

#endif
