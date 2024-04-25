#include "iterator_exceptions.h"
#include "matrix.h"
#include "matrix_exceptions.h"
#include <iostream>

#define EPS 1e-8

template <typename T> void Matrix<T>::allocate(const size_t size)
{
    time_t cur_time = time(NULL);
    int line;

    try {
        line = __LINE__;
        data.reset(new T[size]);
    }
    catch (std::bad_alloc &err) {
        throw MemoryException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T> void Matrix<T>::row_index_check(const size_t i, const int line) const
{
    if (i >= getNRows()) {
        time_t cur_time = time(NULL);
        throw IndexException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T> void Matrix<T>::col_index_check(const size_t j, const int line) const
{
    if (j >= getNCols()) {
        time_t cur_time = time(NULL);
        throw IndexException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T> void Matrix<T>::square_sizes_check(const int line) const
{
    if (getNRows() != getNCols()) {
        time_t cur_time = time(NULL);
        throw SquareSizeException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T> void Matrix<T>::det_check(const int line) const
{
    T det = this->det();

    if (!det) {
        time_t cur_time = time(NULL);
        throw ZeroDetException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T> void Matrix<T>::sum_sizes_check(const Matrix<T> &mtr, const int line) const
{
    if (getNRows() != mtr.getNRows() || getNCols() != mtr.getNCols()) {
        time_t cur_time = time(NULL);
        throw SizesException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T> void Matrix<T>::mul_sizes_check(const Matrix<T> &mtr, const int line) const
{
    if (getNCols() != mtr.getNRows()) {
        time_t cur_time = time(NULL);
        throw SizesException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T> void Matrix<T>::division_by_zero_check(const T &num, const int line) const
{
    if (abs(num) < EPS) {
        time_t cur_time = time(NULL);
        throw DivisionByZeroException(ctime(&cur_time), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}
