#ifndef MATH_MACROS_H_
#define MATH_MACROS_H_

namespace arl
{
#define DATA_ALLOCATION(data, data_size, data_type, alloc_type)                                   \
    try                                                                                           \
    {                                                                                             \
        data = new data_type[data_size];                                                          \
    }                                                                                             \
    catch (std::bad_alloc & ba)                                                                   \
    {                                                                                             \
        std::cerr << alloc_type << " allocation failed, bad_alloc caught: " << ba.what() << '\n'; \
        exit(-1);                                                                                 \
    }

#define AGLMAT_TO_EIGENMAT(agl_mat, eigen_mat)                         \
    {                                                                  \
        assert(agl_mat.isAllocated() && "Agl mat not allocated!");     \
        assert(static_cast<int>(agl_mat.rows()) == eigen_mat.rows() && \
               "Row mismatch between matrices!");                      \
        assert(static_cast<int>(agl_mat.cols()) == eigen_mat.cols() && \
               "Row mismatch between matrices!");                      \
        for (size_t r = 0; r < agl_mat.rows(); r++)                    \
        {                                                              \
            for (size_t c = 0; c < agl_mat.cols(); c++)                \
            {                                                          \
                eigen_mat(r, c) = agl_mat(r, c);                       \
            }                                                          \
        }                                                              \
    }

#define EIGENMAT_TO_AGLMAT(eigen_mat, agl_mat)                         \
    {                                                                  \
        assert(agl_mat.isAllocated() && "Agl mat not allocated!");     \
        assert(static_cast<int>(agl_mat.rows()) == eigen_mat.rows() && \
               "Row mismatch between matrices!");                      \
        assert(static_cast<int>(agl_mat.cols()) == eigen_mat.cols() && \
               "Row mismatch between matrices!");                      \
        for (size_t r = 0; r < agl_mat.rows(); r++)                    \
        {                                                              \
            for (size_t c = 0; c < agl_mat.cols(); c++)                \
            {                                                          \
                agl_mat(r, c) = eigen_mat(r, c);                       \
            }                                                          \
        }                                                              \
    }

/*// clang-format off
#define ASSERT_MATRIX_OK(mat)                                 \
    {                                                         \
        assert(mat.isAllocated() && "Matrix not allocated!"); \
        assert((mat.rows() > 0) && "Num rows is 0!");         \
        assert((mat.cols() > 0) && "Num cols is 0!");
    }
// clang-format on*/

/*// clang-format off
#define ASSERT_VECTOR_OK(vec)                                 \
    {                                                         \
        assert(vec.isAllocated() && "Vector not allocated!"); \
        assert((vec.size() > 0) && "Size is 0!");
    }
// clang-format on*/

}  // namespace arl

#endif
