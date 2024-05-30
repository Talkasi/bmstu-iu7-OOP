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

TEST(sum, matrix_sum_assign)
{
    Matrix<int> expected = {{3, 7, -3}, {46, 13, 6}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> b = {{4, 5, -6}, {23, 1, 3}};

    EXPECT_NO_THROW(a += b);

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

TEST(sum, val_sum_assign)
{
    Matrix<int> expected = {{1, 4, 5}, {25, 14, 5}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 2;

    EXPECT_NO_THROW(a += val);

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

TEST(sum, zero_matrix_sum_assign)
{
    Matrix<int> expected = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> b = {{0, 0, 0}, {0, 0, 0}};

    EXPECT_NO_THROW(a += b);

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

TEST(sum, zero_val_sum_assign)
{
    Matrix<int> expected = {{-1, 2, 3}, {23, 12, 3}};
    Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
    int val = 0;

    EXPECT_NO_THROW(a += val);

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
// TEST(sum, diff_types_sum)
// {
//     Matrix<double> expected = {{-0.766, 36, 26}, {30.3, 82.4, 63.3}};
//     Matrix<int> a = {{-1, 2, 3}, {23, 12, 3}};
//     Matrix<double> b = {{0.234, 34, 23}, {7.3, 70.4, 60.3}};
//     Matrix<double> res(a + b);

//     EXPECT_EQ(a.getNRows(), expected.getNRows());
//     EXPECT_EQ(a.getNCols(), expected.getNCols());

//     EXPECT_EQ(a.isEmpty(), false);
//     EXPECT_EQ(expected.isEmpty(), false);

//     EXPECT_NE(a.begin(), a.end());
//     EXPECT_NE(expected.begin(), expected.end());

//     for (size_t i = 0; i < a.getNRows(); ++i)
//         for (size_t j = 0; j < a.getNCols(); ++j)
//             EXPECT_EQ(a(i, j), expected(i, j));
// }

#endif
