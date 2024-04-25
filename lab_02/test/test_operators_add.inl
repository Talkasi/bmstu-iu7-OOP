#ifndef TEST_OPERATORS_ADD_HPP
#define TEST_OPERATORS_ADD_HPP
#include "matrix.h"
#include <gtest/gtest.h>

TEST(sum, matrix_sum)
{
    Matrix<int> expected = {{3, 7, -3}, {46, 13, 6}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> b = {{4, 5, -6}, {23, 1, 3}};

    Matrix<int> res(a + b);

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

TEST(sum, val_sum)
{
    Matrix<int> expected = {{1, 4, 5}, {25, 14, 5}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 2;

    Matrix<int> res(a + val);

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

TEST(sum, zero_matrix_sum)
{
    Matrix<int> expected = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> b = {{0, 0, 0}, {0, 0, 0}};

    Matrix<int> res(a + b);

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

TEST(sum, zero_val_sum)
{
    Matrix<int> expected = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 0;

    Matrix<int> res(a + val);

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

#endif
