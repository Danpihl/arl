#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "arl/math/general_matrix_math_functions.h"
#include "arl/math/math.h"
#include "test/unit_tests/math/math_test_utils.h"

namespace arl
{
namespace
{
class VectorIndexingTest : public testing::Test
{
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(VectorIndexingTest, VectorIndexingLogical)
{
    const Vector<int> v0({1, 4, 3, 2, 6, 3, 1, 0, -3, 2, 5, 4});
    const Vector<bool> v_ind({1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1});

    const Vector<int> vres = v0(v_ind);

    size_t idx = 0;
    for (size_t k = 0; k < v_ind.size(); k++)
    {
        if (v_ind(k))
        {
            ASSERT_EQ(v0(k), vres(idx));
            idx++;
        }
    }
}

TEST_F(VectorIndexingTest, VectorIndexingIndices)
{
    const Vector<int> v0({1, 4, 3, 2, 6, 3, 1, 0, -3, 2, 5, 4});
    const Vector<size_t> v_ind0({0, 1, 0, 4, 2, 6, 2});
    const Vector<int> v_ind1({0, 1, 0, 4, 2, 6, 2, 1, 6, 3, 2, 4, 6, 2, 3});

    const Vector<int> vres0 = v0(v_ind0);
    const Vector<int> vres1 = v0(v_ind1);

    for (size_t k = 0; k < v_ind0.size(); k++)
    {
        const size_t idx = v_ind0(k);
        ASSERT_EQ(v0(idx), vres0(k));
    }

    for (size_t k = 0; k < v_ind1.size(); k++)
    {
        const size_t idx = v_ind1(k);
        ASSERT_EQ(v0(idx), vres1(k));
    }
}

TEST_F(VectorIndexingTest, VectorIndexingIndicesAngLogical)
{
    const Vector<int> v0({1, 4, 3, 2, 6, 3, 1, 0, -3, 2, 5, 4});
    const Vector<size_t> v_ind0({0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1});
    const Vector<size_t> v_ind1({0, 1, 2, 5, 2, 4, 2, 4, 1, 3, 4, 0});

    const Vector<int> vres0 = v0(v_ind0);
    const Vector<int> vres1 = v0(v_ind1);
    const Vector<int> v_exp0 = {4, 2, 6, 0, -3, 5, 4};

    for (size_t k = 0; k < v_exp0.size(); k++)
    {
        ASSERT_EQ(vres0(k), v_exp0(k));
    }
    ASSERT_EQ(v_exp0.size(), vres0.size());

    for (size_t k = 0; k < v_ind1.size(); k++)
    {
        const size_t idx = v_ind1(k);
        ASSERT_EQ(v0(idx), vres1(k));
    }
}

TEST_F(VectorIndexingTest, VectorEndIndexing)
{
    const Vector<int> v({0, 1, 0, 4, 2, 6, 2, 1, 6, 3, 2, 4, 6, 2, 3});

    ASSERT_EQ(v(EndIndex()), v(v.size() - 1));

    for (size_t k = 0; k < v.size(); k++)
    {
        const size_t end_idx = v.size() - 1 - k;
        ASSERT_EQ(v(EndIndex(-static_cast<int>(k))), v(end_idx));
    }
}

}  // namespace
}  // namespace arl
