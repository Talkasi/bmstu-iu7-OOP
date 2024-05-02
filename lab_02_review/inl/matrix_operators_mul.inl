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

template <NumType T> Matrix<T> &Matrix<T>::operator*=(const T &val)
{
    for (size_t i = 0; i < n_rows * n_cols; ++i)
        data[i] *= val;

    return *this;
}

template <NumType T> Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &matrix)
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

    // TODO(Talkasi): Separate this
    n_rows = res.n_rows;
    n_cols = res.n_cols;
    for (size_t i = 0; i < n_rows; ++i) {
        for (size_t j = 0; j < n_cols; ++j) {
            size_t index = i * res.getNCols() + j;
            data[index] = res.data[index];
        }
    }

    return *this;
}

template <NumType T> template <NumType U> auto Matrix<T>::operator*(const U &val) const
{
    Matrix<decltype((*this)(0, 0) - val)> res(*this);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        res.data[i] *= val;

    return res;
}

template <NumType T> template <NumType U> auto Matrix<T>::operator*(const Matrix<U> &matrix) const
{
    mul_sizes_check(matrix, __LINE__);
    Matrix<decltype((*this)(0, 0) - matrix(0, 0))> res(n_rows, matrix.getNCols());
    decltype((*this)(0) * matrix(0)) sum;

    for (size_t i = 0; i < n_rows; ++i) {
        for (size_t j = 0; j < matrix.getNCols(); ++j) {
            sum = 0;
            for (size_t k = 0; k < n_cols; ++k)
                sum += this->at(i, k) * matrix.at(k, j);
            res(i, j) = sum;
        }
    }

    return res;
}
