#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T> class Iterator : public BaseIterator
{
public:
    Iterator() = default;
    Iterator(Matrix<T> &matrix, const size_t i = 0);
    Iterator(const Iterator<T> &iter) = default;
    Iterator(Iterator<T> &&iter) noexcept = default;

    ~Iterator() noexcept = default;

    T &operator[](const size_t index);
    T *operator->();
    T &operator*();

    operator bool() const noexcept;
    auto operator<=>(const Iterator<T> &other) const;

    Iterator<T> &operator++();
    Iterator<T> operator++(int);

    Iterator<T> &operator--();
    Iterator<T> operator--(int);

    template <typename U> Iterator<T> operator+(const U val) const;
    template <typename U> Iterator<T> operator-(const U val) const;
    template <typename U> Iterator<T> &operator+=(const U val);
    template <typename U> Iterator<T> &operator-=(const U val);

    std::ptrdiff_t operator-(const Iterator<T> &iter);

    Iterator<T> &operator=(const Iterator<T> &other);
    Iterator<T> &operator=(Iterator<T> &&other) noexcept;

protected:
    // TODO(Talkasi)

private:
    std::weak_ptr<T[]> data;
};

#endif // ITERATOR_H
