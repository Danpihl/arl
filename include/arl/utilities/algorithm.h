#ifndef ARL_ALGORITHM_H_
#define ARL_ALGORITHM_H_

#include <vector>

#include "arl/math/lin_alg.h"

namespace arl
{
template <typename T, class UnaryFunction> void forEachApply(Vector<T>& vec, const UnaryFunction& f)
{
    for (size_t k = 0; k < vec.size(); k++)
    {
        f(vec(k));
    }
}

template <typename T, class UnaryFunction>
void forEachApply(std::vector<T>& vec, const UnaryFunction& f)
{
    for (size_t k = 0; k < vec.size(); k++)
    {
        f(vec[k]);
    }
}

template <typename T, class UnaryFunction>
std::vector<T> forEachApplyToNewVec(const std::vector<T>& vec, const UnaryFunction& f)
{
    if (vec.size() == 0)
    {
        return std::vector<T>();
    }
    else
    {
        std::vector<T> res(vec.size());
        for (size_t k = 0; k < vec.size(); k++)
        {
            res[k] = f(vec[k]);
        }
        return res;
    }
}

template <typename T, class UnaryFunction>
Vector<T> forEachApplyToNewVec(const Vector<T>& vec, const UnaryFunction& f)
{
    if (vec.size() == 0)
    {
        return Vector<T>();
    }
    else
    {
        Vector<T> res(vec.size());
        for (size_t k = 0; k < vec.size(); k++)
        {
            res(k) = f(vec(k));
        }
        return res;
    }
}

}  // namespace arl

#endif
