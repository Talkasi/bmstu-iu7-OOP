#ifndef MATRIX_H
#define MATRIX_H

template <typename T> class Matrix : public BaseMatrix
{
public:
    // TODO(Talkasi): Understand where to put noexcept and do it.

    /* LIFETIME */
    Matrix() noexcept;
    explicit Matrix(const size_t n_rows, const size_t n_cols);
    Matrix(const size_t n_rows, const size_t n_cols, const T &fill_elem);
    Matrix(const size_t n_rows, const size_t n_cols, T **matrix);
    Matrix(const std::initializer_list<std::initializer_list<T>> init);

    // TODO(Talkasi): When do we need to declare explicit functions?
    explicit Matrix(const Matrix<T> &matrix);
    Matrix(Matrix<T> &&tmp_matrix) noexcept;

    ~Matrix();

    /* OPERATIONS */
    /* Comparison */
    bool operator==(const Matrix<T> &matrix) const;
    bool operator!=(const Matrix<T> &matrix) const;
    bool isSizeEqual(const Matrix<T> &matrix) const;
    bool isSizeNotEqual(const Matrix<T> &matrix) const;

    // TODO(Talkasi): Think about iterators.
    // template <IterType IterT> Matrix(IterT i_beg, IterT i_end);

    // TODO(Talkasi): Think if it is needed to rename typename T. Do we need smth else?
    template <typename T> auto operator<=>(const Matrix<T> &other) const;

    /* Assignment */
    Matrix<T> &operator=(const Matrix<T> &matrix);
    Matrix<T> &operator=(Matrix<T> &&tmp_matrix) noexcept;
    Matrix<T> &operator=(const std::initializer_list<std::initializer_list<T>> &init);

    /* Addition */
    Matrix<T> operator+(const T &val) const;
    Matrix<T> operator+(const Matrix<T> &matrix) const;
    Matrix<T> &operator+=(const T &val) const;
    Matrix<T> &operator+=(const Matrix<T> &matrix) const;

    /* Substraction */
    Matrix<T> operator-(const T &val) const;
    Matrix<T> operator-(const Matrix<T> &matrix) const;
    Matrix<T> &operator-=(const T &val) const;
    Matrix<T> &operator-=(const Matrix<T> &matrix) const;

    /* Multiplication */
    // TODO(Talkasi): Think about vector multiplication?
    Matrix<T> operator*(const T &val) const;
    Matrix<T> operator*(const Matrix<T> &matrix) const;
    Matrix<T> &operator*=(const T &val) const;
    Matrix<T> &operator*=(const Matrix<T> &matrix) const;

    /* Division */
    Matrix<T> operator/(const T &val) const;
    Matrix<T> operator/=(const T &val) const;

    /* Indexation */
    T &at(const size_t i, const size_t j);
    T &operator()(const size_t i, const size_t j);
    const T &at(const size_t i, const size_t j) const;
    const T &operator()(const size_t i, const size_t j) const;

    /* ITERATORS */
    // TODO(Talkasi)

    /* OTHER METHODS */
    /* Bool info */
    bool isEmpty() const;
    bool isIdentity() const;
    bool isDiagonal() const;
    bool isZero() const;
    bool isSquare() const;

    static Matrix<T> zeroMatrix(const size_t rows, const size_t cols);
    static Matrix<T> identityMatrix(const size_t rows, const size_t cols);

    T det() const;
    Matrix<T> invert() const;
    Matrix<T> transpose() const;

    void swap_rows(const size_t f_row, const size_t s_row);
    void swap_cols(const size_t f_col, const size_t s_col);

protected:
    // TODO(Talkasi)

private:
    std::shared_ptr<T[]> data = nullptr;
};

#endif // MATRIX_H
