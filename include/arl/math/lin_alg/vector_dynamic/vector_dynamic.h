// Copyright 2019 Arrowtwig
#ifndef VECTOR_DYNAMIC_H_
#define VECTOR_DYNAMIC_H_

#include "arl/math/math_core.h"

#include "arl/math/misc/math_macros.h"
#include "arl/utilities/logging.h"

#include <cmath>
#include <utility>

namespace arl
{
template <typename T> Vector<T>::Vector() : data_(nullptr), vector_length_(0), is_allocated_(false)
{
}

template <typename T> Vector<T>::Vector(const size_t vector_length) : is_allocated_(true)
{
    vector_length_ = vector_length;

    DATA_ALLOCATION(data_, vector_length, T, "Vector");
}

template <typename T> Vector<T>::Vector(const Vector<T>& v) : is_allocated_(true)
{
    vector_length_ = v.size();

    DATA_ALLOCATION(data_, v.size(), T, "Vector");

    for (size_t k = 0; k < v.size(); k++)
    {
        data_[k] = v(k);
    }
}

template <typename T> Vector<T>::~Vector()
{
    if (is_allocated_)
    {
        delete[] data_;
        is_allocated_ = false;
    }
}

template <typename T> Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
    ASSERT(v.isAllocated()) << "Input vector not allocated before assignment!";

    if (this != &v)
    {
        if (is_allocated_)
        {
            if (v.size() != vector_length_)
            {
                delete[] data_;
                DATA_ALLOCATION(data_, v.size(), T, "Vector");
            }
        }
        else
        {
            DATA_ALLOCATION(data_, v.size(), T, "Vector");
        }
        vector_length_ = v.size();

        // DATA_ALLOCATION(data_, v.size(), T, "Vector");
        is_allocated_ = true;

        for (size_t k = 0; k < v.size(); k++)
        {
            data_[k] = v(k);
        }
    }

    return *this;
}

template <typename T> Vector<T>::Vector(const std::initializer_list<T>& il)
{
    ASSERT(il.size() > 0) << "Tried to initialize with empty vector!";

    DATA_ALLOCATION(data_, il.size(), T, "Vector");
    is_allocated_ = true;

    vector_length_ = il.size();

    size_t idx = 0;
    for (auto list_element : il)
    {
        data_[idx] = list_element;
        idx++;
    }
}

template <typename T> Vector<T>::Vector(const std::vector<T>& v)
{
    ASSERT(v.size() > 0) << "Tried to initialize with empty vector!";

    if (v.size() == 0)
    {
        vector_length_ = 0;
        is_allocated_ = false;
    }
    else
    {
        vector_length_ = v.size();

        DATA_ALLOCATION(data_, v.size(), T, "Vector");
        is_allocated_ = true;

        size_t idx = 0;
        for (auto vec_element : v)
        {
            data_[idx] = vec_element;
            idx++;
        }
    }
}

// Vector functions

template <typename T> T& Vector<T>::operator()(const size_t idx)
{
    assert(idx < vector_length_ && is_allocated_);
    return data_[idx];
}

template <typename T> const T& Vector<T>::operator()(const size_t idx) const
{
    assert(idx < vector_length_ && is_allocated_);
    return data_[idx];
}

template <typename T> T& Vector<T>::operator()(const EndIndex& end_idx)
{
    const size_t idx = static_cast<size_t>(static_cast<int>(vector_length_) - 1 + end_idx.offset);
    assert((idx < vector_length_) && is_allocated_);
    return data_[idx];
}

template <typename T> const T& Vector<T>::operator()(const EndIndex& end_idx) const
{
    const size_t idx = static_cast<size_t>(static_cast<int>(vector_length_) - 1 + end_idx.offset);
    assert((idx < vector_length_) && is_allocated_);
    return data_[idx];
}

template <typename T>
template <typename Y>
Vector<T> Vector<T>::operator()(const Vector<Y>& idx_vector) const
{
    static_assert(std::is_same<Y, bool>::value || std::is_same<Y, size_t>::value ||
                      std::is_same<Y, int>::value,
                  "You must use either integer or boolean for indexing type!");
    std::vector<T> std_vec;
    if (std::is_same<Y, bool>::value)
    {
        assert(idx_vector.size() == vector_length_);
        for (size_t k = 0; k < idx_vector.size(); k++)
        {
            if (idx_vector(k))
            {
                std_vec.push_back(data_[k]);
            }
        }
    }
    else
    {
        bool only_one_or_zero = true;
        for (size_t k = 0; k < idx_vector.size(); k++)
        {
            if (!((idx_vector(k) == 0) || (idx_vector(k) == 1)))
            {
                only_one_or_zero = false;
                break;
            }
        }
        if ((idx_vector.size() == vector_length_) && only_one_or_zero)
        {
            for (size_t k = 0; k < idx_vector.size(); k++)
            {
                if (idx_vector(k))
                {
                    std_vec.push_back(data_[k]);
                }
            }
        }
        else
        {
            for (size_t k = 0; k < idx_vector.size(); k++)
            {
                const size_t idx = idx_vector(k);
                assert((idx < vector_length_) && (idx >= 0));
                std_vec.push_back(data_[idx]);
            }
        }
    }

    return Vector<T>(std_vec);
}

template <typename T> Vector<T> Vector<T>::operator()(const IndexSpan& idx_span) const
{
    ASSERT(idx_span.from < vector_length_) << "Lower index exceeds vector size!";
    ASSERT(idx_span.from < vector_length_) << "Upper index exceeds vector size!";
    ASSERT(idx_span.from <= idx_span.to) << "Lower index larger than upper index!";
    const size_t new_vector_length = idx_span.to - idx_span.from + 1;
    Vector<T> vres(new_vector_length);

    for (size_t k = 0; k < new_vector_length; k++)
    {
        vres(k) = data_[k + idx_span.from];
    }
    return vres;
}

template <typename T> size_t Vector<T>::size() const
{
    return vector_length_;
}

template <typename T> size_t Vector<T>::numElements() const
{
    return vector_length_;
}

template <typename T> bool Vector<T>::isAllocated() const
{
    return is_allocated_;
}

template <typename T> void Vector<T>::fill(T val)
{
    assert(is_allocated_ && "Tried to fill un allocated vector!");
    for (size_t k = 0; k < vector_length_; k++)
    {
        data_[k] = val;
    }
}

template <typename T> void Vector<T>::resize(const size_t vector_length)
{
    if (is_allocated_)
    {
        delete[] data_;
    }

    is_allocated_ = true;
    DATA_ALLOCATION(data_, vector_length, T, "Vector");

    vector_length_ = vector_length;
}

template <typename T> size_t Vector<T>::countNumNonZeroElements() const
{
    ASSERT(is_allocated_) << "Vector not allocated!";
    size_t cnt = 0;
    for (size_t k = 0; k < vector_length_; k++)
    {
        if (data_[k])
        {
            cnt++;
        }
    }
    return cnt;
}

template <typename T> size_t Vector<T>::endIndex() const
{
    return vector_length_ - 1;
}

template <typename T> T* Vector<T>::getDataPointer() const
{
    return data_;
}

template <typename T> T Vector<T>::norm() const
{
    T d = 0.0f;
    for (size_t k = 0; k < vector_length_; k++)
    {
        d = d + data_[k] * data_[k];
    }
    return std::sqrt(d);
}

template <typename T> T Vector<T>::squaredNorm() const
{
    T d = 0.0f;
    for (size_t k = 0; k < vector_length_; k++)
    {
        d = d + data_[k] * data_[k];
    }
    return d;
}

template <typename T> Point<T> Vector<T>::mirrorPointInThis(const Point<T>& point_to_mirror) const
{
    // Mirrors "point_to_mirror" in "this"
    return *this - this->vectorBetweenPoints(point_to_mirror);
}

template <typename T> T Vector<T>::angleBetweenVectors(const Vector<T>& v) const
{
    const T dot_product = (*this) * v;
    return std::acos(dot_product / ((this->norm()) * (v.norm())));
}

// Non class methods

template <typename T> std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
    std::string s = "[ ";
    for (size_t k = 0; k < v.size(); k++)
    {
        s = s + std::to_string(v(k));
        if (k != v.size() - 1)
        {
            s = s + ", ";
        }
    }
    s = s + " ]";
    os << s;

    return os;
}

template <typename T> T operator*(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    T d = 0.0;
    for (size_t k = 0; k < v0.size(); k++)
    {
        d = d + v0(k) * v1(k);
    }
    return d;
}

template <typename T> Vector<T> operator*(const T f, const Vector<T>& v)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = f * v(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator*(const Vector<T>& v, const T f)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = f * v(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator^(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<T> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) * v1(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator/(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<T> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) / v1(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator/(const Vector<T>& v, const T f)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) / f;
    }
    return v_res;
}

template <typename T> Vector<T> operator/(const T f, const Vector<T>& v)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = f / v(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator+(const Vector<T>& v, const T f)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) + f;
    }
    return v_res;
}

template <typename T> Vector<T> operator+(const T f, const Vector<T>& v)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) + f;
    }
    return v_res;
}

template <typename T> Vector<T> operator-(const Vector<T>& v, const T f)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) - f;
    }
    return v_res;
}

template <typename T> Vector<T> operator-(const T f, const Vector<T>& v)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = f - v(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator-(const Vector<T>& v)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = -v(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator+(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<T> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) + v1(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator-(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<T> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) - v1(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator==(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) == v1(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator==(const Vector<T>& v, const T s)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) == s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator==(const T s, const Vector<T>& v)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) == s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator!=(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) != v1(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator!=(const Vector<T>& v, const T s)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) != s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator!=(const T s, const Vector<T>& v)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) != s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator<(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) < v1(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator<(const Vector<T>& v, const T s)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) < s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator<(const T s, const Vector<T>& v)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s < v(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator>(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) > v1(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator>(const Vector<T>& v, const T s)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) > s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator>(const T s, const Vector<T>& v)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s > v(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator<=(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) <= v1(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator<=(const Vector<T>& v, const T s)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) <= s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator<=(const T s, const Vector<T>& v)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s <= v(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator>=(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) >= v1(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator>=(const Vector<T>& v, const T s)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) >= s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator>=(const T s, const Vector<T>& v)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s >= v(k);
    }
    return v_res;
}

//

template <typename T> Vector<T> operator&(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<T> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) & v1(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator&(const Vector<T>& v, const T s)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) & s;
    }
    return v_res;
}

template <typename T> Vector<T> operator&(const T s, const Vector<T>& v)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s & v(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator|(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<T> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) | v1(k);
    }
    return v_res;
}

template <typename T> Vector<T> operator|(const Vector<T>& v, const T s)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) | s;
    }
    return v_res;
}

template <typename T> Vector<T> operator|(const T s, const Vector<T>& v)
{
    Vector<T> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s | v(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator&&(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) && v1(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator&&(const Vector<T>& v, const T s)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) && s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator&&(const T s, const Vector<T>& v)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s && v(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator||(const Vector<T>& v0, const Vector<T>& v1)
{
    assert(v0.size() == v1.size());
    Vector<bool> v_res(v0.size());
    for (size_t k = 0; k < v0.size(); k++)
    {
        v_res(k) = v0(k) || v1(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator||(const Vector<T>& v, const T s)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = v(k) || s;
    }
    return v_res;
}

template <typename T> Vector<bool> operator||(const T s, const Vector<T>& v)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = s || v(k);
    }
    return v_res;
}

template <typename T> Vector<bool> operator!(const Vector<T>& v)
{
    Vector<bool> v_res(v.size());
    for (size_t k = 0; k < v.size(); k++)
    {
        v_res(k) = !v(k);
    }
    return v_res;
}

template <typename T> void fillVectorWithArray(arl::Vector<T>& v, const T* a)
{
    assert(v.isAllocated() && "You must allocate your vector before filling it!");
    for (size_t k = 0; k < v.size(); k++)
    {
        v(k) = a[k];
    }
}

template <typename T> Vector<T> vectorCat(const Vector<T>& v0, const Vector<T>& v1)
{
    ASSERT(v0.isAllocated() && v1.isAllocated()) << "Input vectors not allocated!";
    Vector<T> vres(v0.size() + v1.size());

    for (size_t k = 0; k < v0.size(); k++)
    {
        vres(k) = v0(k);
    }

    for (size_t k = v0.size(); k < vres.size(); k++)
    {
        vres(k) = v1(k - v0.size());
    }

    return vres;
}

template <typename T> void Vector<T>::removeElementAtIndex(const size_t idx)
{
    ASSERT(is_allocated_) << "Vector not allocated!";
    ASSERT(idx < vector_length_) << "Tried to remove element outside bounds!";

    T* temp_data;

    DATA_ALLOCATION(temp_data, vector_length_ - 1, T, "Vector");

    size_t current_idx = 0;
    for (size_t k = 0; k < vector_length_; k++)
    {
        if (current_idx != idx)
        {
            temp_data[current_idx] = data_[k];
            current_idx++;
        }
    }
    delete[] data_;
    data_ = temp_data;
    vector_length_ = vector_length_ - 1;
}

template <typename T> void Vector<T>::removeElementsAtIndices(const IndexSpan& idx_span)
{
    ASSERT(is_allocated_) << "Vector not allocated!";
    ASSERT(idx_span.from <= idx_span.to) << "To index smaller than from index!";
    ASSERT(idx_span.to < vector_length_) << "Tried to remove elements outside bounds!";
    if (idx_span.from == idx_span.to)
    {
        LOG_WARNING() << "From and to indices are equal!";
    }

    T* temp_data;
    size_t num_elements_to_remove = idx_span.to - idx_span.from + 1;
    DATA_ALLOCATION(temp_data, vector_length_ - num_elements_to_remove, T, "Vector");

    ASSERT((vector_length_ - num_elements_to_remove) > 0) << "Tried to remove all elements!";

    size_t current_idx = 0;
    for (size_t k = 0; k < vector_length_; k++)
    {
        if (current_idx < idx_span.from || idx_span.to < current_idx)
        {
            temp_data[current_idx] = data_[k];
            current_idx++;
        }
    }
    delete[] data_;
    data_ = temp_data;
    vector_length_ = vector_length_ - num_elements_to_remove;
}

template <typename T> Vector<T> Vector<T>::normalized() const
{
    Vector<T> v_res(vector_length_);
    T d = 0.0f;
    for (size_t k = 0; k < vector_length_; k++)
    {
        d = d + data_[k] * data_[k];
    }
    d = std::sqrt(d);

    for (size_t k = 0; k < vector_length_; k++)
    {
        v_res(k) = data_[k] / d;
    }
    return v_res;
}

template <typename T> Vector<T> Vector<T>::vectorBetweenPoints(const Point<T>& end_point) const
{
    // "This" is start point
    return end_point - *this;
}

template <typename T>
Vector<T> Vector<T>::normalizedVectorBetweenPoints(const Point<T>& end_point) const
{
    // "This" is start point
    return (end_point - *this).normalized();
}

}  // namespace arl

#endif
