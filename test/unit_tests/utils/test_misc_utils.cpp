#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "arl/utilities/filesystem_utils.h"
#include "arl/utilities/logging.h"
#include "arl/utilities/misc_utils.h"

namespace arl
{
class MiscUtilsTest : public testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(MiscUtilsTest, TestTime)
{
    // Time t = getTimeNow();
    // PRINT() << t.toString();
}

}  // namespace arl
