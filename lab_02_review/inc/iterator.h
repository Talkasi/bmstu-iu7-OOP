#ifndef ITERATOR_H
#define ITERATOR_H
#include "concept.h"
#include "matrix.h"
#include <memory>

template <NumType T> class Matrix;

template <NumType T> class Iterator : public BaseIterator
{
public:
    Iterator() = default;
    explicit Iterator(shared_ptr<Matrix<T>> &matrix) noexcept;
    Iterator(const Iterator<T> &iter) = default;
    Iterator(Iterator<T> &&iter) noexcept = default;

    ~Iterator() noexcept;

    T &operator[](size_t index);
    std::shared_ptr<T> operator->();
    T &operator*();

    operator bool() const;
    auto operator<=>(const T &other) const
    {
        return this->index <=> other.index;
    }

    Iterator<T> &operator++();
    Iterator<T> operator++(int);

    Iterator<T> &operator--();
    Iterator<T> operator--(int);

    Iterator<T> operator+(size_t val) const;
    Iterator<T> operator-(size_t val) const;
    Iterator<T> &operator+=(size_t val);
    Iterator<T> &operator-=(size_t val);

protected:
    std::shared_ptr<T> get_ptr() const;
    void expride_check(int line) const;
    void index_check(int line) const;

private:
    std::weak_ptr<Matrix<T>> ptr;
    size_t n_rows = 0;
    size_t n_cols = 0;
};

#include "iterator.inl"

#endif // ITERATOR_H
