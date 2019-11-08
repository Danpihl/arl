#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "arl/math/math.h"
#include "test/unit_tests/math/math_test_utils.h"

namespace arl
{
namespace
{
class GeneralMatrixMathFunctionsTest : public testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(GeneralMatrixMathFunctionsTest, MatConcatenate)
{
    const double eps = 1e-7;

    const Matrixd m0({{4, 2}, {1, 5}});
    const Matrixd m1({{3, 5, 1, 4, 3}, {6, 2, 4, 2, 1}});
    const Matrixd m2({{6, 3, 4}, {0, 4, 3}});
    const Matrixd m3({{6}, {3}});
    const Matrixd m_exp({{4, 2, 3, 5, 1, 4, 3, 6, 3, 4, 6}, {1, 5, 6, 2, 4, 2, 1, 0, 4, 3, 3}});

    const Matrixd m_act = concatenateHorizontally({m0, m1, m2, m3});
    ASSERT_MATRIX_NEAR_MATRIX(m_exp, m_act, eps);
}

} // namespace
} // namespace arl
