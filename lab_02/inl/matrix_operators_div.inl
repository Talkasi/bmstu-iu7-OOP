#include "concept.h"
#include "matrix.h"
#include <iostream>

template <NumType T> Matrix<T> Matrix<T>::operator/(const T &val) const
{
    division_by_zero_check(val, __LINE__);

    Matrix<T> res(*this);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        res.data[i] /= val;

    return res;
}

template <NumType T> Matrix<T> &Matrix<T>::operator/=(const T &val) const
{
    division_by_zero_check(val, __LINE__);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        data[i] /= val;

    return *this;
}
