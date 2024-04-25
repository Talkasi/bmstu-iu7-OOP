#include "matrix.h"
#include <iostream>

template <typename T> Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix)
{
    n_rows = matrix.n_rows;
    n_cols = matrix.n_cols;
    allocate(matrix.n_rows * matrix.n_cols);

    for (size_t i = 0; i < n_rows * n_cols; ++i)
        data[i] = matrix.data[i];

    return *this;
}

template <typename T> Matrix<T> &Matrix<T>::operator=(Matrix<T> &&tmp_matrix) noexcept
{
    n_rows = tmp_matrix.n_rows;
    n_cols = tmp_matrix.n_cols;
    data = tmp_matrix.data;
    tmp_matrix.data.reset();
    return *this;
}

template <typename T> Matrix<T> &Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> &elems)
{
    this->n_rows = elems.size();
    this->n_cols = elems.begin()->size();
    allocate(this->n_rows * this->n_cols);

    auto elem_i = elems.begin();

    for (size_t i = 0; elem_i < elems.end(); i++, elem_i++) {
        auto elem_j = elem_i->begin();

        for (size_t j = 0; j < elem_i->end(); j++, elem_j++)
            data[i * n_cols + j] = *elem_j;
    }

    return *this;
}
