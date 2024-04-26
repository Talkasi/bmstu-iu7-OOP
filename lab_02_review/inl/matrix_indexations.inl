#include "concept.h"
#include "matrix.h"
#include <iostream>

template <NumType T> T &Matrix<T>::at(size_t i, size_t j)
{
    row_index_check(i, __LINE__);
    col_index_check(j, __LINE__);
    return data[i * n_cols + j];
}

template <NumType T> T &Matrix<T>::operator()(size_t i, size_t j)
{
    return at(i, j);
}

template <NumType T> const T &Matrix<T>::at(size_t i, size_t j) const
{
    row_index_check(i, __LINE__);
    col_index_check(j, __LINE__);
    return data[i * n_cols + j];
}

template <NumType T> const T &Matrix<T>::operator()(size_t i, size_t j) const
{
    return at(i, j);
}
