#ifndef MATRIX_H
#define MATRIX_H
#include "base_matrix.h"
#include "concept.h"
#include "const_iterator.h"
#include "iterator.h"
#include <initializer_list>
#include <memory>

template <NumType T> class Matrix : public BaseMatrix
{
public:
    friend Iterator<T>;
    friend ConstIterator<T>;

    /* LIFETIME */
    Matrix() noexcept;
    explicit Matrix(const size_t n_rows, const size_t n_cols);
    Matrix(const size_t n_rows, const size_t n_cols, const T &fill_elem);
    Matrix(const size_t n_rows, const size_t n_cols, const T **matrix);
    Matrix(const std::initializer_list<std::initializer_list<T>> elems);

    explicit Matrix(const Matrix<T> &matrix);
    Matrix(Matrix<T> &&tmp_matrix) noexcept;

    ~Matrix() override = default;

    /* OPERATIONS */
    /* Comparison */
    bool operator==(const Matrix<T> &matrix) const;
    bool operator!=(const Matrix<T> &matrix) const;
    bool isSizeEqual(const Matrix<T> &matrix) const;
    bool isSizeNotEqual(const Matrix<T> &matrix) const;

    template <NumType U> auto operator<=>(const Matrix<U> &other) const;

    /* Assignment */
    Matrix<T> &operator=(const Matrix<T> &matrix);
    Matrix<T> &operator=(Matrix<T> &&tmp_matrix) noexcept;
    Matrix<T> &operator=(std::initializer_list<std::initializer_list<T>> &elems);

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
    Matrix<T> operator*(const T &val) const;
    Matrix<T> operator*(const Matrix<T> &matrix) const;
    Matrix<T> &operator*=(const T &val) const;
    Matrix<T> &operator*=(const Matrix<T> &matrix) const;

    /* Division */
    Matrix<T> operator/(const T &val) const;
    Matrix<T> &operator/=(const T &val) const;

    /* Indexation */
    T &at(const size_t i, const size_t j);
    T &operator()(const size_t i, const size_t j);
    const T &at(const size_t i, const size_t j) const;
    const T &operator()(const size_t i, const size_t j) const;

    /* ITERATORS */
    Iterator<T> begin() noexcept;
    Iterator<T> end() noexcept;

    ConstIterator<T> begin() const noexcept;
    ConstIterator<T> end() const noexcept;
    ConstIterator<T> cbegin() const noexcept;
    ConstIterator<T> cend() const noexcept;

    /* OTHER METHODS */
    /* Bool info */
    bool isIdentity() const;
    bool isZero() const;
    bool isSquare() const;

    static Matrix<T> zeroMatrix(const size_t n_rows, const size_t n_cols);
    static Matrix<T> identityMatrix(const size_t n_rows, const size_t n_cols);

    T det() const;
    Matrix<T> invert() const;
    Matrix<T> &transpose() const;

    void swap_rows(const size_t f_row, const size_t s_row);
    void swap_cols(const size_t f_col, const size_t s_col);

protected:
    void allocate(const size_t size);

    /* CHECKS */
    void row_index_check(const size_t i, const int line) const;
    void col_index_check(const size_t j, const int line) const;
    void sum_sizes_check(const Matrix<T> &mtr, const int line) const;
    void mul_sizes_check(const Matrix<T> &mtr, const int line) const;
    void square_sizes_check(const int line) const;
    void division_by_zero_check(const T &num, const int line) const;
    void det_check(const int line) const;

    static void exclude_copy(Matrix<T> &dst, const Matrix<T> &src, const size_t ex_row, const size_t ex_col);

private:
    std::shared_ptr<T[]> data = nullptr;
};

#include "matrix_assignment.inl"
#include "matrix_functions.inl"
#include "matrix_indexations.inl"
#include "matrix_iterators.inl"
#include "matrix_lifetime.inl"
#include "matrix_logic.inl"
#include "matrix_operators_add.inl"
#include "matrix_operators_div.inl"
#include "matrix_operators_mul.inl"
#include "matrix_operators_sub.inl"
#include "matrix_tools.inl"

#endif // MATRIX_H
