#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

template <typename T> class ConstIterator : public BaseIterator
{
public:
    ConstIterator() = default;
    ConstIterator(Matrix<T> &matrix, const size_t i = 0);
    ConstIterator(const ConstIterator<T> &iter) = default;
    ConstIterator(ConstIterator<T> &&iter) noexcept = default;

    ~ConstIterator() noexcept = default;

    const T &operator[](const size_t index) const;
    const T *operator->() const;
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
    // TODO(Talkasi)

private:
    std::weak_ptr<T[]> data;
};

#endif // CONST_ITERATOR_H
