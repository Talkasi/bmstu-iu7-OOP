#ifndef TEST_OPERATORS_DIFF_HPP
#define TEST_OPERATORS_DIFF_HPP
#include "matrix.h"
#include <gtest/gtest.h>

TEST(sub, matrix_sub)
{
    Matrix<int> expected = {{-5, -3, 9}, {0, 11, 0}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> b = {{4, 5, -6}, {23, 1, 3}};

    Matrix<int> res(a - b);

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

TEST(sub, val_sub)
{
    Matrix<int> expected = {{-3, 0, 1}, {21, 10, 1}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 2;

    Matrix<int> res(a - val);

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

TEST(sub, zero_matrix_sub)
{
    Matrix<int> expected = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> b = {{0, 0, 0}, {0, 0, 0}};

    Matrix<int> res(a - b);

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

TEST(sub, zero_val_sub)
{
    Matrix<int> expected = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 0;

    Matrix<int> res(a - val);

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

TEST(sub, matrix_sub_assign)
{
    Matrix<int> expected = {{-5, -3, 9}, {0, 11, 0}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> b = {{4, 5, -6}, {23, 1, 3}};

    EXPECT_NO_THROW(a -= b);

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

TEST(sub, val_sub_assign)
{
    Matrix<int> expected = {{-3, 0, 1}, {21, 10, 1}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 2;

    EXPECT_NO_THROW(a -= val);

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

TEST(sub, zero_matrix_sub_assign)
{
    Matrix<int> expected = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> b = {{0, 0, 0}, {0, 0, 0}};

    EXPECT_NO_THROW(a -= b);

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

TEST(sub, zero_val_sub_assign)
{
    Matrix<int> expected = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 0;

    EXPECT_NO_THROW(a -= val);

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
#endif
