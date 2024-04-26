#ifndef TEST_OPERATORS_MUL_HPP
#define TEST_OPERATORS_MUL_HPP
#include "matrix.h"
#include <gtest/gtest.h>

TEST(mul, matrix_mul)
{
    Matrix<int> expected = {{-16, 16}, {-35, 15}};
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};
    Matrix<int> b = {{-7, 5}, {2, -1}, {4, 3}};

    Matrix<int> res(a * b);

    EXPECT_EQ(res.getNRows(), expected.getNRows());
    EXPECT_EQ(res.getNCols(), expected.getNCols());

    EXPECT_EQ(res.isEmpty(), false);
    EXPECT_EQ(expected.isEmpty(), false);

    EXPECT_NE(res.begin(), res.end());
    EXPECT_NE(expected.begin(), expected.end());

    for (size_t i = 0; i < res.getNRows(); ++i)
        for (size_t j = 0; j < res.getNCols(); ++j)
            EXPECT_EQ(res(i, j), expected(i, j));
}

TEST(mul, val_mul)
{
    Matrix<int> expected = {{-2, 4, 6}, {46, 24, 6}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 2;

    Matrix<int> res(a * val);

    EXPECT_EQ(res.getNRows(), expected.getNRows());
    EXPECT_EQ(res.getNCols(), expected.getNCols());

    EXPECT_EQ(res.isEmpty(), false);
    EXPECT_EQ(expected.isEmpty(), false);

    EXPECT_NE(res.begin(), res.end());
    EXPECT_NE(expected.begin(), expected.end());

    for (size_t i = 0; i < res.getNRows(); ++i)
        for (size_t j = 0; j < res.getNCols(); ++j)
            EXPECT_EQ(res(i, j), expected(i, j));
}

TEST(mul, zero_matrix_mul)
{
    Matrix<int> expected = {{0, 0}, {0, 0}};
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};
    Matrix<int> b = {{0, 0}, {0, 0}, {0, 0}};

    Matrix<int> res(a * b);

    EXPECT_EQ(res.getNRows(), expected.getNRows());
    EXPECT_EQ(res.getNCols(), expected.getNCols());

    EXPECT_EQ(res.isEmpty(), false);
    EXPECT_EQ(expected.isEmpty(), false);

    EXPECT_NE(res.begin(), res.end());
    EXPECT_NE(expected.begin(), expected.end());

    for (size_t i = 0; i < res.getNRows(); ++i)
        for (size_t j = 0; j < res.getNCols(); ++j)
            EXPECT_EQ(res(i, j), expected(i, j));
}

TEST(mul, zero_val_mul)
{
    Matrix<int> expected = {{0, 0, 0}, {0, 0, 0}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 0;

    Matrix<int> res(a * val);

    EXPECT_EQ(res.getNRows(), expected.getNRows());
    EXPECT_EQ(res.getNCols(), expected.getNCols());

    EXPECT_EQ(res.isEmpty(), false);
    EXPECT_EQ(expected.isEmpty(), false);

    EXPECT_NE(res.begin(), res.end());
    EXPECT_NE(expected.begin(), expected.end());

    for (size_t i = 0; i < res.getNRows(); ++i)
        for (size_t j = 0; j < res.getNCols(); ++j)
            EXPECT_EQ(res(i, j), expected(i, j));
}

TEST(mul, matrix_mul_assign)
{
    Matrix<int> expected = {{-16, 16}, {-35, 15}};
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};
    Matrix<int> b = {{-7, 5}, {2, -1}, {4, 3}};

    EXPECT_NO_THROW(a *= b);

    EXPECT_EQ(a.getNRows(), expected.getNRows());
    EXPECT_EQ(a.getNCols(), expected.getNCols());

    EXPECT_EQ(a.isEmpty(), false);
    EXPECT_EQ(expected.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());
    EXPECT_NE(expected.begin(), expected.end());

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), expected(i, j));
}

TEST(mul, val_mul_assign)
{
    Matrix<int> expected = {{-2, 4, 6}, {46, 24, 6}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 2;

    EXPECT_NO_THROW(a *= val);

    EXPECT_EQ(a.getNRows(), expected.getNRows());
    EXPECT_EQ(a.getNCols(), expected.getNCols());

    EXPECT_EQ(a.isEmpty(), false);
    EXPECT_EQ(expected.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());
    EXPECT_NE(expected.begin(), expected.end());

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), expected(i, j));
}

TEST(mul, zero_matrix_mul_assign)
{
    Matrix<int> expected = {{0, 0}, {0, 0}};
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};
    Matrix<int> b = {{0, 0}, {0, 0}, {0, 0}};

    EXPECT_NO_THROW(a *= b);

    EXPECT_EQ(a.getNRows(), expected.getNRows());
    EXPECT_EQ(a.getNCols(), expected.getNCols());

    EXPECT_EQ(a.isEmpty(), false);
    EXPECT_EQ(expected.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());
    EXPECT_NE(expected.begin(), expected.end());

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), expected(i, j));
}

TEST(mul, zero_val_mul_assign)
{
    Matrix<int> expected = {{0, 0, 0}, {0, 0, 0}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 0;

    EXPECT_NO_THROW(a *= val);

    EXPECT_EQ(a.getNRows(), expected.getNRows());
    EXPECT_EQ(a.getNCols(), expected.getNCols());

    EXPECT_EQ(a.isEmpty(), false);
    EXPECT_EQ(expected.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());
    EXPECT_NE(expected.begin(), expected.end());

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), expected(i, j));
}

TEST(mul, diff_types_mul)
{
    Matrix<double> expected = {{-21.78, 14.5}, {-27.5, 21.1}};
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};
    Matrix<double> b = {{-7.34, 5.3}, {2.5, -1.2}, {.4, .3}};
    Matrix<double> res = a * b;

    EXPECT_EQ(res.getNRows(), expected.getNRows());
    EXPECT_EQ(res.getNCols(), expected.getNCols());

    EXPECT_EQ(res.isEmpty(), false);
    EXPECT_EQ(expected.isEmpty(), false);

    EXPECT_NE(res.begin(), res.end());
    EXPECT_NE(expected.begin(), expected.end());

    for (size_t i = 0; i < res.getNRows(); ++i)
        for (size_t j = 0; j < res.getNCols(); ++j)
            EXPECT_DOUBLE_EQ(res(i, j), expected(i, j));
}

#endif
