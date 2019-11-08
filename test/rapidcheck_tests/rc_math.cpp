#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

#include <cmath>

// RC_PARAMS="max_size=120" ./cpp/build/modules/math_core/rapidcheck-math-core

namespace arl
{
namespace
{
RC_GTEST_PROP(RapidCheckMath, Test1, (float f1, float f2, float f3, float q1, float q2, float q3))
{
    RC_ASSERT(true);
    RC_ASSERT(true);
    RC_ASSERT(true);
}

RC_GTEST_PROP(RapidCheckMath, Test2, ())
{
    const auto t = *rc::gen::inRange<int>(0, 360);
}

class MathCoreRapidCheck : public ::testing::Test
{
protected:
    float f;

    MathCoreRapidCheck() {}

    virtual ~MathCoreRapidCheck() {}

    virtual void SetUp() {}

    virtual void TearDown() {}
};

RC_GTEST_FIXTURE_PROP(MathCoreRapidCheck, Test3, ())
{
    RC_ASSERT(true);
}

} // namespace
} // namespace arl
