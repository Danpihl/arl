#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "arl/utilities/logging.h"

#include "arl/utilities/data_logging/data_logger.h"

namespace arl
{
class DataLoggerTest : public testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(DataLoggerTest, TestInit)
{
    ASSERT_FALSE(Var_isInitialized());
    initDataLogging();
    ASSERT_TRUE(Var_isInitialized());
    deInitDataLogging();
    ASSERT_FALSE(Var_isInitialized());
}

std::map<std::string, std::pair<std::vector<std::string>, std::vector<int>>> getDataMap()
{
    const std::pair<std::vector<std::string>, std::vector<int>> p0 = {{"var0", "var1"},
                                                                      {4, 7, 2, -6}};
    const std::pair<std::vector<std::string>, std::vector<int>> p1 = {{"x0", "y0", "z0"},
                                                                      {0, -1, 2}};
    const std::pair<std::vector<std::string>, std::vector<int>> p2 = {
        {"var4", "var5", "var6", "var7"}, {-12, 3, 72, 11, 6}};

    const std::map<std::string, std::pair<std::vector<std::string>, std::vector<int>>> data_map = {
        {"file0", p0}, {"file1", p1}, {"file2", p2}};

    return data_map;
}

TEST_F(DataLoggerTest, TestReadData)
{
    initDataLogging();
    const auto data_map = getDataMap();

    for (const std::pair<std::string, std::pair<std::vector<std::string>, std::vector<int>>>
             file_key_val_pair : data_map)
    {
        const std::string file_name = file_key_val_pair.first;
        for (const std::string var_name : file_key_val_pair.second.first)
        {
            for (const int data_to_save : file_key_val_pair.second.second)
            {
                dumpData<char>(file_name, var_name, data_to_save);
            }
        }
    }

    deInitDataLogging();
}

TEST_F(DataLoggerTest, TestDataIsCorrect)
{
    initDataLogging();
    const auto data_map = getDataMap();

    for (const std::pair<std::string, std::pair<std::vector<std::string>, std::vector<int>>>
             file_key_val_pair : data_map)
    {
        const std::string file_name = file_key_val_pair.first;
        for (const std::string var_name : file_key_val_pair.second.first)
        {
            for (const int data_to_save : file_key_val_pair.second.second)
            {
                dumpData<char>(file_name, var_name, data_to_save);
            }
        }
    }

    for (const std::pair<std::string, std::pair<std::vector<std::string>, std::vector<int>>>
             file_key_val_pair : data_map)
    {
        const std::string file_name = file_key_val_pair.first;
        for (const std::string var_name : file_key_val_pair.second.first)
        {
            const Variable var = Var_classInstance().data[file_name][var_name];

            const char* data_ptr = var.getDataVectorPointer();
            const size_t num_elements = var.getNumElements();

            const std::vector<int> gt_vec = file_key_val_pair.second.second;
            ASSERT_EQ(gt_vec.size(), num_elements);

            for (size_t k = 0; k < gt_vec.size(); k++)
            {
                ASSERT_EQ(gt_vec[k], data_ptr[k]);
            }
        }
    }

    deInitDataLogging();
}

TEST_F(DataLoggerTest, TestAddingVariablesAndFiles)
{
    initDataLogging();

    const std::map<std::string, std::vector<std::string>> data_map_small = {
        {"file0", {"var0", "var1"}},
        {"file1", {"x0", "y0", "z0"}},
        {"file2", {"var4", "var5", "var6", "var7"}},
    };

    for (const std::pair<std::string, std::vector<std::string>> file_key_val_pair : data_map_small)
    {
        const std::string file_name = file_key_val_pair.first;
        for (const std::string var_name : file_key_val_pair.second)
        {
            dumpData<char>(file_name, var_name, 0);
        }
    }

    const std::vector<std::string> file_names_act = Var_classInstance().getFileNames();
    ASSERT_EQ(data_map_small.size(), file_names_act.size());

    for (const std::pair<std::string, std::vector<std::string>> file_key_val_pair : data_map_small)
    {
        const std::string file_name = file_key_val_pair.first;

        ASSERT_TRUE(std::find(file_names_act.begin(), file_names_act.end(), file_name) !=
                    file_names_act.end());

        const std::vector<std::string> variables_act =
            Var_classInstance().getVariablesInFile(file_name);

        for (const std::string var_name : file_key_val_pair.second)
        {
            ASSERT_TRUE(std::find(variables_act.begin(), variables_act.end(), var_name) !=
                        variables_act.end());
        }
    }

    deInitDataLogging();
}

}  // namespace arl
