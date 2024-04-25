#include "concept.h"
#include "matrix.h"
#include <iostream>

template <NumType T> bool Matrix<T>::isIdentity() const
{
    if (n_rows != n_cols)
        return false;

    for (size_t i = 0; i < n_rows; ++i) {
        for (size_t j = 0; j < n_cols; ++j) {
            if (i == j) {
                if (data[i * n_cols + j] != 1)
                    return false;
            }
            else {
                if (data[i * n_cols + j])
                    return false;
            }
        }
    }

    return true;
}

template <NumType T> bool Matrix<T>::isZero() const
{
    for (size_t i = 0; i < n_rows; ++i)
        for (size_t j = 0; j < n_cols; ++j)
            if (data[i * n_cols + j])
                return false;

    return true;
}

template <NumType T> Matrix<T> Matrix<T>::zeroMatrix(const size_t n_rows, const size_t n_cols)
{
    Matrix<T> res(n_rows, n_cols);

    for (size_t i = 0; i < n_rows; ++i)
        for (size_t j = 0; j < n_cols; ++j)
            res.data[i * n_cols + j] = 0;

    return res;
}

template <NumType T> Matrix<T> Matrix<T>::identityMatrix(const size_t n_rows, const size_t n_cols)
{
    Matrix<T> res(n_rows, n_cols);

    for (size_t i = 0; i < n_rows; ++i)
        for (size_t j = 0; j < n_cols; ++j)
            res.data[i * n_cols + j] = (i == j);

    return res;
}

template <NumType T> Matrix<T> &Matrix<T>::transpose() const
{
    Matrix<T> transposed_matrix(n_cols, n_rows);

    for (size_t i = 0; i < n_rows; ++i)
        for (size_t j = 0; j < n_cols; ++j)
            transposed_matrix.at(j, i) = at(i, j);

    return transposed_matrix;
}

template <NumType T>
void Matrix<T>::exclude_copy(Matrix<T> &dst, const Matrix<T> &src, const size_t ex_row, const size_t ex_col)
{
    size_t row_index, col_index;

    for (size_t i = 0; i < src.getNRows() - 1; ++i)
        for (size_t j = 0; j < src.getNCols() - 1; ++j) {
            row_index = i >= ex_row ? i + 1 : i;
            col_index = j >= ex_col ? j + 1 : j;
            dst.data[i * src.get_columns() + j] = src.data[row_index * src.get_columns() + col_index];
        }
}

template <NumType T> T Matrix<T>::det() const
{
    square_sizes_check(__LINE__);

    if (n_rows == 1)
        return data[0];

    if (n_rows == 2)
        return data[0] * data[3] - data[2] * data[1];

    T res = {};
    Matrix<T> tmp(n_rows - 1, n_cols - 1);

    for (size_t i = 0; i < n_rows; ++i) {
        Matrix<T>::exclude_copy(tmp, *this, 0, i);
        T minor = tmp.det();

        if (i % 2 == 1)
            minor = -minor;

        res += minor * data[i];
    }

    return res;
}

template <NumType T> Matrix<T> Matrix<T>::invert() const
{
    square_sizes_check(__LINE__);
    det_check(__LINE__);

    Matrix<T> res(n_rows, n_cols);
    Matrix<T> tmp(n_rows - 1, n_cols - 1);
    T value = {};
    T det = det();

    for (size_t i = 0; i < n_rows; ++i)
        for (size_t j = 0; j < n_cols; ++j) {
            Matrix<T>::exclude_copy(tmp, *this, i, j);
            value = tmp.det() / det;

            if ((i + j) & 1)
                value = -value;

            res(j, i) = value;
        }

    return res;
}

template <NumType T> void Matrix<T>::swap_rows(const size_t i, const size_t j)
{
    row_index_check(i, __LINE__);
    row_index_check(j, __LINE__);

    if (i != j)
        for (size_t col_i = 0; col_i < n_cols; ++col_i)
            std::swap(at(i, col_i), at(j, col_i));
}

template <NumType T> void Matrix<T>::swap_cols(const size_t i, const size_t j)
{
    row_index_check(i, __LINE__);
    row_index_check(j, __LINE__);

    if (i != j)
        for (size_t row_i = 0; row_i < n_rows; ++row_i)
            std::swap(at(row_i, i), at(row_i, j));
}
