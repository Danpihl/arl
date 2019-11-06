#ifndef MATRIX_FIXED_FUNCTIONS_H_
#define MATRIX_FIXED_FUNCTIONS_H_

#include <cstdlib>

namespace arl
{

template <typename U, typename ...Us> constexpr size_t numCols(const U& mat, __attribute__((unused)) const Us&... matrices)
{
    return mat.cols();
}

template <typename U, typename ...Us> constexpr size_t numRows(const U& mat, __attribute__((unused)) const Us&... matrices)
{
    return mat.rows();
}

template <typename U> constexpr size_t totalNumRowsInternal(const U& m)
{
    return m.rows();
}

template <typename U, typename ...Us> constexpr size_t totalNumRowsInternal(const U& m, const Us&... matrices)
{

    return totalNumRowsInternal(matrices...) + m.rows();
}

template <typename ...Us> constexpr size_t totalNumRows(const Us&... matrices)
{
    return totalNumRowsInternal(matrices...);
}

template <typename U> constexpr size_t totalNumColsInternal(const U& m)
{
    return m.cols();
}

template <typename U, typename ...Us> constexpr size_t totalNumColsInternal(const U& m, const Us&... matrices)
{

    return totalNumColsInternal(matrices...) + m.cols();
}

template <typename ...Us> constexpr size_t totalNumCols(const Us&... matrices)
{
    return totalNumColsInternal(matrices...);
}

template <size_t R, size_t C, typename T, typename U> void hCatFixedMatricesInternal(size_t col_idx,
                                                                                MatrixFixed<R, C, T> &m_res,
                                                                                const U& mat)
{
    for(size_t r = 0; r < mat.rows(); r++)
    {
        for(size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r, c + col_idx) = mat(r, c);
        }
    }
}

template <size_t R, size_t C, typename T, typename U, typename ...Us> void hCatFixedMatricesInternal(size_t col_idx,
                                                                                                MatrixFixed<R, C, T> &m_res,
                                                                                                const U& mat,
                                                                                                const Us&... matrices)
{
    for(size_t r = 0; r < mat.rows(); r++)
    {
        for(size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r, c + col_idx) = mat(r, c);
        }
    }

    hCatFixedMatricesInternal(col_idx + mat.cols(), m_res, matrices...);
}

template <size_t R, size_t C, typename U, typename ...Us> MatrixFixed<R, C, typename U::data_type> hCatFixedMatricesInternal(const U& mat, const Us&... matrices)
{
    MatrixFixed<R, C, typename U::data_type> m_res;

    for(size_t r = 0; r < mat.rows(); r++)
    {
        for(size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r, c) = mat(r, c);
        }
    }

    hCatFixedMatricesInternal(mat.cols(), m_res, matrices...);

    return m_res;
}

template <size_t R, size_t C, typename T, typename U> void vCatFixedMatricesInternal(size_t row_idx,
                                                                                     MatrixFixed<R, C, T> &m_res,
                                                                                     const U& mat)
{
    for(size_t r = 0; r < mat.rows(); r++)
    {
        for(size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r + row_idx, c) = mat(r, c);
        }
    }
}

template <size_t R, size_t C, typename T, typename U, typename ...Us> void vCatFixedMatricesInternal(size_t row_idx,
                                                                                                     MatrixFixed<R, C, T> &m_res,
                                                                                                     const U& mat,
                                                                                                     const Us&... matrices)
{
    for(size_t r = 0; r < mat.rows(); r++)
    {
        for(size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r + row_idx, c) = mat(r, c);
        }
    }

    vCatFixedMatricesInternal(row_idx + mat.rows(), m_res, matrices...);
}

template <size_t R, size_t C, typename U, typename ...Us> MatrixFixed<R, C, typename U::data_type> vCatFixedMatricesInternal(const U& mat,
                                                                                                                             const Us&... matrices)
{
    MatrixFixed<R, C, typename U::data_type> m_res;

    for(size_t r = 0; r < mat.rows(); r++)
    {
        for(size_t c = 0; c < mat.cols(); c++)
        {
            m_res(r, c) = mat(r, c);
        }
    }

    vCatFixedMatricesInternal(mat.rows(), m_res, matrices...);

    return m_res;
}

#define hCatFixedMatrices(...) hCatFixedMatricesInternal<numRows(__VA_ARGS__), totalNumCols(__VA_ARGS__)>(__VA_ARGS__)
#define vCatFixedMatrices(...) vCatFixedMatricesInternal<totalNumRows(__VA_ARGS__), numCols(__VA_ARGS__)>(__VA_ARGS__)

}

#endif
