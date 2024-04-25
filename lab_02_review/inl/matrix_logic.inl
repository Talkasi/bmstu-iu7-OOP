#include "concept.h"
#include "matrix.h"
#include <iostream>

template <NumType T> template <NumType U> auto Matrix<T>::operator<=>(const Matrix<U> &other) const
{
    return n_rows * n_cols <=> other.n_rows * other.n_cols;
}

template <NumType T> bool Matrix<T>::operator==(const Matrix<T> &matrix) const
{
    if (n_rows != matrix.n_rows || n_cols != matrix.n_cols)
        return false;

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        if (data[i] != matrix.data[i])
            return false;

    return true;
}

template <NumType T> bool Matrix<T>::operator!=(const Matrix<T> &matrix) const
{
    if (n_rows != matrix.n_rows || n_cols != matrix.n_cols)
        return true;

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        if (data[i] != matrix.data[i])
            return true;

    return false;
}

template <NumType T> bool Matrix<T>::isSizeEqual(const Matrix<T> &matrix) const
{
    if (n_rows != matrix.n_rows || n_cols != matrix.n_cols)
        return false;

    return true;
}

template <NumType T> bool Matrix<T>::isSizeNotEqual(const Matrix<T> &matrix) const
{
    if (n_rows != matrix.n_rows || n_cols != matrix.n_cols)
        return true;

    return false;
}
