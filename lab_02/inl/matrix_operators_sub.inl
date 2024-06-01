#include "concept.h"
#include "matrix.h"
#include <iostream>

template <NumType T> Matrix<T> Matrix<T>::operator-(const T &val) const
{
    Matrix<T> res(*this);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        res.data[i] -= val;

    return res;
}

template <NumType T> Matrix<T> Matrix<T>::operator-(const Matrix<T> &matrix) const
{
    sum_sizes_check(matrix, __LINE__);

    Matrix<T> res(*this);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        res.data[i] -= matrix.data[i];

    return res;
}

template <NumType T> Matrix<T> &Matrix<T>::operator-=(const T &val)
{
    for (size_t i = 0; i < n_rows * n_cols; ++i)
        data[i] -= val;

    return *this;
}

template <NumType T> Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &matrix)
{
    sum_sizes_check(matrix, __LINE__);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        data[i] -= matrix.data[i];

    return *this;
}
