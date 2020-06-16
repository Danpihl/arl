#ifndef MATH_MACROS_H_
#define MATH_MACROS_H_

#include "arl/utilities/logging.h"

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

#define AGLMAT_TO_EIGENMAT(agl_mat, eigen_mat)                       \
    {                                                                \
        ASSERT(agl_mat.isAllocated()) << "Agl mat not allocated!";   \
        ASSERT(static_cast<int>(agl_mat.rows()) == eigen_mat.rows()) \
            << "Row mismatch between matrices!";                     \
        ASSERT(static_cast<int>(agl_mat.cols()) == eigen_mat.cols()) \
            << "Row mismatch between matrices!";                     \
        for (size_t r = 0; r < agl_mat.rows(); r++)                  \
        {                                                            \
            for (size_t c = 0; c < agl_mat.cols(); c++)              \
            {                                                        \
                eigen_mat(r, c) = agl_mat(r, c);                     \
            }                                                        \
        }                                                            \
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

#define ASSERT_MAT_VALID(mat)                             \
    ASSERT(mat.isAllocated()) << "Matrix not allocated!"; \
    ASSERT(mat.rows() > 0) << "Number of rows is 0!";     \
    ASSERT(mat.cols() > 0) << "Number of cols is 0!"

#define ASSERT_VEC_VALID(vec)                             \
    ASSERT(vec.isAllocated()) << "Matrix not allocated!"; \
    ASSERT(vec.rows() > 0) << "Vector size is 0!";

#define ASSERT_MAT_VALID_INTERNAL()                   \
    ASSERT(is_allocated_) << "Matrix not allocated!"; \
    ASSERT(num_rows_ > 0) << "Number of rows is 0!";  \
    ASSERT(num_cols_ > 0) << "Number of cols is 0!"

#define ASSERT_VEC_VALID_INTERNAL()                   \
    ASSERT(is_allocated_) << "Vector not allocated!"; \
    ASSERT(vector_length_ > 0) << "Number of elements is 0!"

}  // namespace arl

#endif
