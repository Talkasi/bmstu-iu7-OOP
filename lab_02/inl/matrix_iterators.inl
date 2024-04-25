#include "concept.h"
#include "matrix.h"
#include <iostream>

template <NumType T> Iterator<T> Matrix<T>::begin() noexcept
{
    Iterator<T> iter(*this);

    return iter;
}

template <NumType T> Iterator<T> Matrix<T>::end() noexcept
{
    Iterator<T> iter(*this);

    return iter + n_rows * n_cols;
}

template <NumType T> ConstIterator<T> Matrix<T>::begin() const noexcept
{
    ConstIterator<T> iter(*this);

    return iter;
}

template <NumType T> ConstIterator<T> Matrix<T>::end() const noexcept
{
    ConstIterator<T> iter(*this);

    return iter + n_rows * n_cols;
}

template <NumType T> ConstIterator<T> Matrix<T>::cbegin() const noexcept
{
    ConstIterator<T> iter(*this);

    return iter;
}

template <NumType T> ConstIterator<T> Matrix<T>::cend() const noexcept
{
    ConstIterator<T> iter(*this);

    return iter + n_rows * n_cols;
}
