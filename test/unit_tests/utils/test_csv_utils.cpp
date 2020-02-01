#include <unistd.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "arl/utilities/csv_utils.h"
#include "arl/utilities/filesystem_utils.h"
#include "arl/utilities/logging.h"
#include "arl/utilities/misc_utils.h"

namespace arl
{
class CsvUtilsTest : public testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(CsvUtilsTest, TestWrite)
{
    const size_t num_rows = 4;

    std::vector<std::vector<int>> data(num_rows);
    for (size_t r = 0; r < num_rows; r++)
    {
        const size_t num_cols = (rand() % 20) + 4;
        data[r].resize(num_cols);
        for (size_t c = 0; c < num_cols; c++)
        {
            data[r][c] = rand() % 30;
        }
    }
    writeIntCsvFile("./", "test_output.csv", data);
}

}  // namespace arl
