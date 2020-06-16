#ifndef MATRIX_FIXED_CLASS_DEF_H_
#define MATRIX_FIXED_CLASS_DEF_H_

#include <cstdlib>
#include <utility>

#include "arl/math/misc/forward_decl.h"

namespace arl
{
template <size_t R, size_t C, typename T> class MatrixFixed
{
private:
    T data_[R * C];
    const size_t num_rows_;
    const size_t num_cols_;

public:
    typedef T data_type;

    constexpr MatrixFixed();
    MatrixFixed(const MatrixFixed<R, C, T>& mf);
    MatrixFixed<R, C, T>(const std::initializer_list<std::initializer_list<T>>& il);
    MatrixFixed<R, C, T>& operator=(const MatrixFixed<R, C, T>& m);

    void switchRows(const size_t r0, const size_t r1);
    void switchCols(const size_t c0, const size_t c1);

    T* getDataPointer() const;
    constexpr size_t rows() const;
    constexpr size_t cols() const;

    T& operator()(const size_t r, const size_t c);
    const T& operator()(const size_t r, const size_t c) const;
};
}  // namespace arl

#endif
