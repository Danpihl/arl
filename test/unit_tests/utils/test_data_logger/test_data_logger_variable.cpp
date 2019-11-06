#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "arl/utilities/logging.h"

#include "arl/utilities/data_logging/data_logger.h"

namespace arl
{
class DataLoggerVariableTest : public testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

template <typename T> std::string dummyFunction()
{
    return extractTypeFromTemplateType(__PRETTY_FUNCTION__);
}

TEST_F(DataLoggerVariableTest, TestBasics)
{
    struct ASimpleStruct
    {
        int k;               // If we don't have any variables, "sizeof()" won't work
        int returnK() const  // To make unused variable warnings go away
        {
            return k;
        }
    };

    ASSERT_EQ(dummyFunction<float>(), "float");
    ASSERT_EQ(dummyFunction<size_t>(), "unsigned long");
    ASSERT_EQ(dummyFunction<size_t*>(), "unsigned long*");
    ASSERT_EQ(dummyFunction<float*>(), "float*");
    ASSERT_EQ(dummyFunction<std::string>(), "string");
    ASSERT_EQ(dummyFunction<int>(), "int");
    ASSERT_EQ(dummyFunction<int*>(), "int*");
    ASSERT_EQ(dummyFunction<ASimpleStruct>(), "ASimpleStruct");
    ASSERT_EQ(dummyFunction<ASimpleStruct*>(), "ASimpleStruct*");
    ASSERT_EQ(dummyFunction<std::vector<int>>(), "vector<int>");
    ASSERT_EQ(dummyFunction<std::vector<std::string>>(), "vector<string>");
    ASSERT_EQ(dummyFunction<std::vector<double>>(), "vector<double>");
    ASSERT_EQ(dummyFunction<std::vector<bool>>(), "vector<bool>");
}

TEST_F(DataLoggerVariableTest, Test1)
{
    std::vector<Variable> var_vec;
    for (size_t k = 0; k < 10; k++)
    {
        const std::string name = "var" + std::to_string(k * 30);
        var_vec.push_back(createVariable<double>(name));

        ASSERT_EQ(var_vec[k].name, name);
        ASSERT_EQ(var_vec[k].name_length, name.length());
        ASSERT_EQ(var_vec[k].type_name, "double");
        ASSERT_EQ(var_vec[k].type_name_length, std::string("double").length());
        ASSERT_EQ(static_cast<size_t>(var_vec[k].num_bytes_per_element), sizeof(double));
    }
}

TEST_F(DataLoggerVariableTest, TestAddMultipleElements)
{
    const std::string name = "var_speed";
    Variable var = createVariable<double>(name);

    const size_t new_num_elements = 3;
    const double d0_exp[3] = {1.4, 2.5, 3.6};
    const double d1_exp[3] = {4.1, 5.2, 6.3};

    double d0_act[3] = {0.0};
    double d1_act[3] = {0.0};

    var.addMultipleElements(d0_exp, new_num_elements);
    var.addMultipleElements(d1_exp, new_num_elements);

    const char* data_ptr = var.getDataVectorPointer();

    char* d0_act_ptr = reinterpret_cast<char*>(d0_act);
    char* d1_act_ptr = reinterpret_cast<char*>(d1_act);

    for (size_t k = 0; k < new_num_elements * sizeof(double); k++)
    {
        d0_act_ptr[k] = data_ptr[k];
        d1_act_ptr[k] = data_ptr[k + new_num_elements * sizeof(double)];
    }

    for (size_t k = 0; k < new_num_elements; k++)
    {
        ASSERT_EQ(d0_exp[k], d0_act[k]);
        ASSERT_EQ(d1_exp[k], d1_act[k]);
    }
}

TEST_F(DataLoggerVariableTest, TestAddSingleElement)
{
    const std::string name = "var_speed";
    Variable var = createVariable<double>(name);

    const double d0_exp = 4.0, d1_exp = 0.23;
    double d0_act, d1_act;

    var.addSingleElement(d0_exp);
    var.addSingleElement(d1_exp);

    const char* data_ptr = var.getDataVectorPointer();

    char* d0_act_ptr = reinterpret_cast<char*>(&d0_act);
    char* d1_act_ptr = reinterpret_cast<char*>(&d1_act);
    for (size_t k = 0; k < sizeof(double); k++)
    {
        d0_act_ptr[k] = data_ptr[k];
        d1_act_ptr[k] = data_ptr[k + sizeof(double)];
    }
    ASSERT_EQ(d0_exp, d0_act);
    ASSERT_EQ(d1_exp, d1_act);
}

TEST_F(DataLoggerVariableTest, TestHeaderDataToString)
{
    const std::string name = "var_speed";
    Variable var = createVariable<double>(name);

    const size_t num_elements = 82345;
    var.setNumElements(num_elements);
    ASSERT_EQ(num_elements, var.getNumElements());

    const std::string header_string = var.headerDataToString();

    const std::vector<int> data_gt = {9,   118, 97,  114, 95, 115, 112, 101, 101, 100, 6, 100, 111,
                                      117, 98,  108, 101, 8,  -87, 65,  1,   0,   0,   0, 0,   0};

    ASSERT_EQ(data_gt.size(), header_string.length());
    for (size_t k = 0; k < data_gt.size(); k++)
    {
        ASSERT_EQ(data_gt[k], header_string[k]);
    }

    size_t num_elements_decoded;
    char* data_ptr = reinterpret_cast<char*>(&num_elements_decoded);

    for (size_t k = 0; k < sizeof(size_t); k++)
    {
        data_ptr[k] = header_string[header_string.length() - sizeof(size_t) + k];
    }

    ASSERT_EQ(num_elements_decoded, num_elements);
}

}  // namespace arl
