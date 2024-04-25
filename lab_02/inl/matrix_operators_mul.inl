#include "concept.h"
#include "matrix.h"
#include <iostream>

template <NumType T> Matrix<T> Matrix<T>::operator*(const T &val) const
{
    Matrix<T> res(*this);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        res.data[i] *= val;

    return res;
}

template <NumType T> Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) const
{
    mul_sizes_check(matrix, __LINE__);
    Matrix<T> res(n_rows, matrix.getNCols());

    for (size_t i = 0; i < n_rows; ++i) {
        for (size_t j = 0; j < matrix.getNCols(); ++j) {
            T sum = 0;
            for (size_t k = 0; k < n_cols; ++k)
                sum += this->at(i, k) * matrix.at(k, j);
            res.data[i * matrix.getNCols() + j] = sum;
        }
    }

    return res;
}

template <NumType T> Matrix<T> &Matrix<T>::operator*=(const T &val) const
{
    for (size_t i = 0; i < n_rows * n_cols; ++i)
        data[i] *= val;

    return *this;
}

template <NumType T> Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &matrix) const
{
    mul_sizes_check(matrix, __LINE__);
    Matrix<T> res(n_rows, matrix.getNCols());

    for (size_t i = 0; i < n_rows; ++i) {
        for (size_t j = 0; j < matrix.getNCols(); ++j) {
            T sum = 0;
            for (size_t k = 0; k < n_cols; ++k)
                sum += this->at(i, k) * matrix.at(k, j);
            res[i * matrix.getNCols() + j] = sum;
        }
    }

    return *this;
}
