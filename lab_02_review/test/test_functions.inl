#ifndef TEST_FUNCTIONS_INL
#define TEST_FUNCTIONS_INL
#include "matrix.h"
#include <gtest/gtest.h>

TEST(functions, is_not_identiny_zero)
{
    Matrix<int> identity;
    EXPECT_EQ(identity.isIdentity(), 0);
}

TEST(functions, is_identiny_one)
{
    Matrix<int> identity = Matrix<int>::identityMatrix(1, 1);
    EXPECT_EQ(identity.isIdentity(), 1);
}

TEST(functions, is_not_identiny_one)
{
    Matrix<int> identity = {{0}};
    EXPECT_EQ(identity.isIdentity(), 0);
}

TEST(functions, is_identiny_three)
{
    Matrix<int> identity = Matrix<int>::identityMatrix(3, 3);
    EXPECT_EQ(identity.isIdentity(), 1);
}

TEST(functions, is_not_identity_three)
{
    Matrix<int> identity = {{1, 0, 0}, {0, 1, 0}};
    EXPECT_EQ(identity.isIdentity(), 0);
}

TEST(functions, is_not_zero_zero)
{
    Matrix<int> zero;
    EXPECT_EQ(zero.isZero(), 0);
}

TEST(functions, is_zero_one)
{
    Matrix<int> zero = {{0}};
    EXPECT_EQ(zero.isZero(), 1);
}

TEST(functions, is_not_zero_one)
{
    Matrix<int> zero = {{1}};
    EXPECT_EQ(zero.isZero(), 0);
}

TEST(functions, is_zero_three)
{
    Matrix<int> zero = Matrix<int>::zeroMatrix(3, 9);
    EXPECT_EQ(zero.isZero(), 1);
}

TEST(functions, is_not_zero_three)
{
    Matrix<int> zero = {{0, 0, 0}, {0, 1, 0}};
    EXPECT_EQ(zero.isZero(), 0);
}

TEST(functions, is_square_zero)
{
    Matrix<int> square;
    EXPECT_EQ(square.isSquare(), 1);
}

TEST(functions, is_square_one)
{
    Matrix<int> square = Matrix<int>::zeroMatrix(1, 1);
    EXPECT_EQ(square.isSquare(), 1);
}

TEST(functions, is_not_square_one)
{
    Matrix<int> square = {{1, 2}};
    EXPECT_EQ(square.isSquare(), 0);
}

TEST(functions, is_square_three)
{
    Matrix<int> square = Matrix<int>::zeroMatrix(3, 3);
    EXPECT_EQ(square.isSquare(), 1);
}

TEST(functions, is_not_square_three)
{
    Matrix<int> square = {{0, 0, 0}, {0, 1, 0}};
    EXPECT_EQ(square.isSquare(), 0);
}

TEST(functions, det_two)
{
    Matrix<int> square = {{-2, 3}, {-4, 5}};
    EXPECT_EQ(square.det(), 2);
}

TEST(functions, transpose)
{
    Matrix<int> expected = {{2, 5}, {-3, 4}, {1, -2}};
    Matrix<int> res;
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};

    EXPECT_NO_THROW(res = a.transpose());

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

TEST(functions, swap_rows)
{
    Matrix<int> expected = {{5, 4, -2}, {2, -3, 1}};
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};

    EXPECT_NO_THROW(a.swap_rows(0, 1));

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

TEST(functions, swap_equal_rows)
{
    Matrix<int> expected = {{2, -3, 1}, {5, 4, -2}};
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};

    EXPECT_NO_THROW(a.swap_rows(1, 1));

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

TEST(functions, swap_wrong_rows)
{
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};
    EXPECT_ANY_THROW(a.swap_rows(1, 2));
}

TEST(functions, swap_cols)
{
    Matrix<int> expected = {{-3, 2, 1}, {4, 5, -2}};
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};

    EXPECT_NO_THROW(a.swap_cols(0, 1));

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

TEST(functions, swap_equal_cols)
{
    Matrix<int> expected = {{2, -3, 1}, {5, 4, -2}};
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};

    EXPECT_NO_THROW(a.swap_cols(1, 1));

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

TEST(functions, swap_wrong_cols)
{
    Matrix<int> a = {{2, -3, 1}, {5, 4, -2}};
    EXPECT_ANY_THROW(a.swap_cols(1, 3));
}

#endif
