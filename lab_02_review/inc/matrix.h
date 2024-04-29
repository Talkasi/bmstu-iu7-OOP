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
    /* LIFETIME */
    Matrix() noexcept;
    Matrix(size_t n_rows, size_t n_cols);
    Matrix(size_t n_rows, size_t n_cols, const T &fill_elem);
    Matrix(const T **matrix, size_t n_rows, size_t n_cols);
    Matrix(const std::initializer_list<std::initializer_list<T>> &elems);
    Matrix(const Matrix<T> &matrix);
    Matrix(Matrix<T> &&tmp_matrix) noexcept;
    ~Matrix() noexcept = default;

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
    Matrix<T> &operator=(const std::initializer_list<std::initializer_list<T>> &elems);

    /* Addition */
    Matrix<T> operator+(const T &val) const;
    Matrix<T> operator+(const Matrix<T> &matrix) const;
    Matrix<T> &operator+=(const T &val);
    Matrix<T> &operator+=(const Matrix<T> &matrix);

    /* Substraction */
    Matrix<T> operator-(const T &val) const;
    Matrix<T> operator-(const Matrix<T> &matrix) const;
    Matrix<T> &operator-=(const T &val);
    Matrix<T> &operator-=(const Matrix<T> &matrix);

    /* Multiplication */
    Matrix<T> operator*(const T &val) const;
    Matrix<T> operator*(const Matrix<T> &matrix) const;
    Matrix<T> &operator*=(const T &val);
    Matrix<T> &operator*=(const Matrix<T> &matrix);

    template <NumType U> auto operator*(const U &val) const;
    template <NumType U> auto operator*(const Matrix<U> &matrix) const;

    /* Division */
    Matrix<T> operator/(const T &val) const;
    Matrix<T> &operator/=(const T &val);

    /* Indexation */
    T &at(size_t index);
    T &at(size_t i, size_t j);
    T &operator()(size_t index);
    T &operator()(size_t i, size_t j);
    const T &at(size_t index) const;
    const T &at(size_t i, size_t j) const;
    const T &operator()(size_t index) const;
    const T &operator()(size_t i, size_t j) const;

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

    static Matrix<T> zeroMatrix(size_t n_rows, size_t n_cols);
    static Matrix<T> identityMatrix(size_t n_rows, size_t n_cols);

    T det() const;
    Matrix<T> invert() const;
    Matrix<T> transpose() const;

    void swap_rows(size_t f_row, size_t s_row);
    void swap_cols(size_t f_col, size_t s_col);

protected:
    void allocate(size_t size);

    /* CHECKS */
    void index_check(size_t i, int line) const;
    void row_index_check(size_t i, int line) const;
    void col_index_check(size_t j, int line) const;
    template <NumType U> void sum_sizes_check(const Matrix<U> &mtr, int line) const;
    template <NumType U> void mul_sizes_check(const Matrix<U> &mtr, int line) const;
    void square_sizes_check(int line) const;
    template <NumType U> void division_by_zero_check(const U &num, int line) const;
    void det_check(int line) const;

    static void exclude_copy(Matrix<T> &dst, const Matrix<T> &src, size_t ex_row, size_t ex_col);

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
