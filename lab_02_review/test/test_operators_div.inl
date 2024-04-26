#ifndef TEST_OPERATORS_DIV_HPP
#define TEST_OPERATORS_DIV_HPP
#include "matrix.h"
#include <gtest/gtest.h>

TEST(div, val_div)
{
    Matrix<int> expected = {{0, 1, 1}, {11, 6, 1}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 2;

    Matrix<int> res(a / val);

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

TEST(div, zero_val_div)
{
    Matrix<int> expected = {{0, 1, 1}, {11, 6, 1}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 0;

    EXPECT_ANY_THROW(a / val);
}

TEST(div, val_div_assign)
{
    Matrix<int> expected = {{0, 1, 1}, {11, 6, 1}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 2;

    EXPECT_NO_THROW(a /= val);

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

TEST(div, zero_val_div_assign)
{
    Matrix<int> expected = {{0, 1, 1}, {11, 6, 1}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 0;

    EXPECT_ANY_THROW(a /= val);
}

#endif
