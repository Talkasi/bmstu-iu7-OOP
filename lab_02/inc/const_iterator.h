#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H
#include "base_iterator.h"
#include "matrix.h"
#include <memory>

template <typename T> class Matrix;

template <typename T> class ConstIterator : public BaseIterator
{
public:
    ConstIterator() = default;
    ConstIterator(const Matrix<T> &matrix, const size_t i = 0);
    ConstIterator(const ConstIterator<T> &iter) = default;
    ConstIterator(ConstIterator<T> &&iter) noexcept = default;

    ~ConstIterator() noexcept = default;

    const T &operator[](const size_t index) const;
    const std::shared_ptr<T> *operator->() const;
    const T &operator*() const;

    operator bool() const noexcept;
    auto operator<=>(const ConstIterator<T> &other) const;

    ConstIterator<T> &operator++();
    ConstIterator<T> operator++(int);

    ConstIterator<T> &operator--();
    ConstIterator<T> operator--(int);

    template <typename U> ConstIterator<T> operator+(const U val) const;
    template <typename U> ConstIterator<T> operator-(const U val) const;
    template <typename U> ConstIterator<T> &operator+=(const U val);
    template <typename U> ConstIterator<T> &operator-=(const U val);

    std::ptrdiff_t operator-(const ConstIterator<T> &iter);

    ConstIterator<T> &operator=(const ConstIterator<T> &other);
    ConstIterator<T> &operator=(ConstIterator<T> &&other) noexcept;

protected:
    const std::shared_ptr<T> *get_ptr() const;
    void expride_check(const int line) const;
    void index_check(const int line) const;

private:
    std::weak_ptr<T[]> ptr;
    size_t n_rows = 0;
    size_t n_cols = 0;
};

#endif // CONST_ITERATOR_H
