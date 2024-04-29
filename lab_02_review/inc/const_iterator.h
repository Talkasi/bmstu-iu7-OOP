#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H
#include "base_iterator.h"
#include "concept.h"
#include "matrix.h"
#include <memory>

template <NumType T> class Matrix;

template <NumType T> class ConstIterator : public BaseIterator
{
public:
    ConstIterator() = default;
    explicit ConstIterator(Matrix<T> &matrix) noexcept;
    ConstIterator(std::shared_ptr<T[]> const &dataPtr, size_t nRows, size_t nCols) noexcept;
    ConstIterator(const ConstIterator<T> &iter) = default;
    ConstIterator(ConstIterator<T> &&iter) noexcept = default;

    ~ConstIterator() noexcept = default;

    const T &operator[](size_t index) const;
    const std::shared_ptr<T> operator->() const;
    const T &operator*() const;

    operator bool() const noexcept;
    auto operator<=>(const ConstIterator<T> &other) const
    {
        return this->index <=> other.index;
    }

    ConstIterator<T> &operator++();
    ConstIterator<T> operator++(int);

    ConstIterator<T> &operator--();
    ConstIterator<T> operator--(int);

    ConstIterator<T> operator+(size_t val) const;
    ConstIterator<T> operator-(size_t val) const;
    ConstIterator<T> &operator+=(size_t val);
    ConstIterator<T> &operator-=(size_t val);

    std::ptrdiff_t operator-(const ConstIterator<T> &iter);

    ConstIterator<T> &operator=(const ConstIterator<T> &other);
    ConstIterator<T> &operator=(ConstIterator<T> &&other) noexcept;

protected:
    const std::shared_ptr<T> get_ptr() const;
    void expride_check(int line) const;
    void index_check(int line) const;

private:
    std::weak_ptr<T[]> data;
    size_t n_rows = 0;
    size_t n_cols = 0;
};

#include "const_iterator.inl"

#endif // CONST_ITERATOR_H
