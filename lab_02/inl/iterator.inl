#include "concept.h"
#include "iterator.h"
#include "iterator_exceptions.h"
#include "matrix_exceptions.h"
#include <time.h>

template <NumType T> Iterator<T>::Iterator(Matrix<T> &matrix) noexcept : Iterator<T>(matrix.begin())
{
}

template <NumType T> Iterator<T>::Iterator(std::shared_ptr<T[]> const &dataPtr, size_t nRows, size_t nCols) noexcept
{
    n_rows = nRows;
    n_cols = nCols;
    data = dataPtr;
    index = 0;
}

template <NumType T> Iterator<T>::~Iterator() noexcept = default;

template <NumType T> T &Iterator<T>::operator[](size_t index)
{
    expride_check(__LINE__);
    index_check(__LINE__, index);

    return get_ptr()[index];
}

template <NumType T> std::shared_ptr<T> Iterator<T>::operator->()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    return get_ptr();
}

template <NumType T> T &Iterator<T>::operator*()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    return *get_ptr();
}

template <NumType T> Iterator<T>::operator bool() const
{
    expride_check(__LINE__);

    return n_rows && (index < n_rows * n_cols);
}

template <NumType T> Iterator<T> &Iterator<T>::operator++()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    ++index;
    return *this;
}

template <NumType T> Iterator<T> Iterator<T>::operator++(int)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    Iterator<T> tmp(*this);
    ++index;
    return tmp;
}

template <NumType T> Iterator<T> &Iterator<T>::operator--()
{
    expride_check(__LINE__);
    index_check(__LINE__);

    --index;
    return *this;
}

template <NumType T> Iterator<T> Iterator<T>::operator--(int)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    Iterator<T> tmp(*this);
    --index;
    return tmp;
}

template <NumType T> Iterator<T> Iterator<T>::operator+(size_t val) const
{
    expride_check(__LINE__);
    index_check(__LINE__);

    Iterator<T> tmp(*this);
    tmp.index += val;
    return tmp;
}

template <NumType T> Iterator<T> Iterator<T>::operator-(size_t val) const
{
    expride_check(__LINE__);
    index_check(__LINE__);

    Iterator<T> tmp(*this);
    tmp.index -= val;
    return tmp;
}

template <NumType T> Iterator<T> &Iterator<T>::operator+=(size_t val)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    index += val;
    return *this;
}

template <NumType T> Iterator<T> &Iterator<T>::operator-=(size_t val)
{
    expride_check(__LINE__);
    index_check(__LINE__);

    index -= val;
    return *this;
}

template <NumType T> std::shared_ptr<T> Iterator<T>::get_ptr() const
{
    std::shared_ptr<T[]> tmp = data.lock();
    return std::make_shared<T>(tmp.get()[index]);
}

template <NumType T> void Iterator<T>::expride_check(int line) const
{
    if (data.expired()) {
        time_t curTime = time(NULL);
        throw ExpiredException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}

template <NumType T> void Iterator<T>::index_check(int line) const
{
    if (index >= n_rows * n_cols) {
        time_t curTime = time(NULL);
        throw ItIndexException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __FUNCTION__);
    }
}
