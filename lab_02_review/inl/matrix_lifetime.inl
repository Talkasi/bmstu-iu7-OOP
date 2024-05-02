#include "concept.h"
#include "matrix.h"
#include <iostream>

template <NumType T> Matrix<T>::Matrix() noexcept : BaseMatrix()
{
}

template <NumType T> Matrix<T>::Matrix(size_t n_rows, size_t n_cols) : BaseMatrix(n_rows, n_cols)
{
    allocate(n_rows * n_cols);
    for (size_t i = 0; i < n_rows * n_cols; ++i)
        data[i] = 0;
}

template <NumType T> Matrix<T>::Matrix(size_t n_rows, size_t n_cols, const T &fill_elem) : BaseMatrix(n_rows, n_cols)
{
    allocate(n_rows * n_cols);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        data[i] = fill_elem;
}

template <NumType T> Matrix<T>::Matrix(const T **matrix, size_t n_rows, size_t n_cols) : BaseMatrix(n_rows, n_cols)
{
    allocate(n_rows * n_cols);

    for (size_t i = 0; i < n_rows; ++i)
        for (size_t j = 0; j < n_cols; ++j)
            data[i * n_cols + j] = matrix[i][j];
}

template <NumType T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &elems)
    : BaseMatrix(elems.size(), elems.begin()->size())
{
    allocate(this->n_rows * this->n_cols);

    size_t i = 0;
    for (auto elem_i : elems)
        for (auto elem_j : elem_i)
            data[i++] = elem_j;
}

template <NumType T> Matrix<T>::Matrix(const Matrix<T> &matrix) : BaseMatrix(matrix.n_rows, matrix.n_cols)
{
    allocate(matrix.n_rows * matrix.n_cols);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        data[i] = matrix.data[i];
}

template <NumType T>
Matrix<T>::Matrix(Matrix<T> &&tmp_matrix) noexcept : BaseMatrix(tmp_matrix.n_rows, tmp_matrix.n_cols)
{
    data = tmp_matrix.data;
    tmp_matrix.data.reset();
}
