#include "iterator.h"
#include "iterator_exceptions.h"
#include "matrix_exceptions.h"
#include <time.h>

template <typename T> Iterator<T>::Iterator(Matrix<T> &matrix) noexcept
{
    ptr = matrix.data;
    n_rows = matrix.n_rows;
    n_cols = matrix.n_cols;
    index = 0;
}

template <typename T> Iterator<T>::~Iterator() noexcept = default;

template <typename T> T &Iterator<T>::operator[](const size_t index)
{
    expride_check(__LINE__);
    index_check(__LINE__, index);

    return *(get_ptr() + index);
}

template <typename T> std::shared_ptr<T> *Iterator<T>::operator->()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    return get_ptr();
}

template <typename T> T &Iterator<T>::operator*()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    return *get_ptr();
}

template <typename T> Iterator<T>::operator bool() const
{
    expride_check(__LINE__);

    return n_rows && (index < n_rows * n_cols);
}

template <typename T> Iterator<T> &Iterator<T>::operator++()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    ++index;
    return *this;
}

template <typename T> Iterator<T> Iterator<T>::operator++(int)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    Iterator<T> tmp(*this);
    ++index;
    return tmp;
}

template <typename T> Iterator<T> &Iterator<T>::operator--()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    --index;
    return *this;
}

template <typename T> Iterator<T> Iterator<T>::operator--(int)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    Iterator<T> tmp(*this);
    --index;
    return tmp;
}

template <typename T> Iterator<T> Iterator<T>::operator+(const size_t val) const
{
    expride_check(__LINE__);
    index_check(__LINE__);

    Iterator<T> tmp(*this);
    tmp.index += val;
    return tmp;
}

template <typename T> Iterator<T> Iterator<T>::operator-(const size_t val) const
{
    expride_check(__LINE__);
    index_check(__LINE__);

    Iterator<T> tmp(*this);
    tmp.index -= val;
    return tmp;
}

template <typename T> Iterator<T> &Iterator<T>::operator+=(const size_t val)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    index += val;
    return *this;
}

template <typename T> Iterator<T> &Iterator<T>::operator-=(const size_t val)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    index -= val;
    return *this;
}

template <typename T> std::shared_ptr<T> *Iterator<T>::get_ptr() const
{
    std::shared_ptr<T[]> tmp = ptr.lock();
    return tmp.get() + index;
}

template <typename T> void Iterator<T>::expride_check(const int line) const
{
    if (ptr.expired()) {
        time_t curTime = time(NULL);
        throw ExpiredException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <typename T> void Iterator<T>::index_check(const int line) const
{
    if (index >= n_rows * n_cols) {
        time_t curTime = time(NULL);
        throw ItIndexException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}
