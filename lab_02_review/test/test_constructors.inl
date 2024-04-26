#ifndef TEST_CONSTRUCTORS_INL
#define TEST_CONSTRUCTORS_INL
#include "matrix.h"
#include <cstring>
#include <gtest/gtest.h>

TEST(constructors, test_empty)
{
    Matrix<int> a;
    Matrix<int> b = {};

    EXPECT_EQ(a.getNRows(), 0);
    EXPECT_EQ(a.getNCols(), 0);

    EXPECT_EQ(b.getNRows(), 0);
    EXPECT_EQ(b.getNCols(), 0);

    EXPECT_EQ(a.isEmpty(), true);
    EXPECT_EQ(b.isEmpty(), true);

    EXPECT_NO_THROW(a.begin());
    EXPECT_NO_THROW(b.begin());

    EXPECT_ANY_THROW(a(0, 0));
    EXPECT_ANY_THROW(b(0, 0));
}

TEST(constructors, test_size)
{
    Matrix<int> a(3, 5);

    EXPECT_EQ(a.getNRows(), 3);
    EXPECT_EQ(a.getNCols(), 5);

    EXPECT_EQ(a.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());

    EXPECT_NO_THROW(a(2, 3));

    for (auto elem : a)
        EXPECT_EQ(elem, 0);
}

TEST(constructors, test_size_fill)
{
    Matrix<int> a(3, 5, 30);

    EXPECT_EQ(a.getNRows(), 3);
    EXPECT_EQ(a.getNCols(), 5);

    EXPECT_EQ(a.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());

    EXPECT_NO_THROW(a(1, 2));

    for (auto elem : a)
        EXPECT_EQ(elem, 30);

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), 30);
}

TEST(constructors, test_size_fill_chr)
{
    Matrix<char> a(3, 5, 'a');

    EXPECT_EQ(a.getNRows(), 3);
    EXPECT_EQ(a.getNCols(), 5);

    EXPECT_EQ(a.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());

    EXPECT_NO_THROW(a(1, 2));

    for (auto elem : a)
        EXPECT_EQ(elem, 'a');

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), 'a');
}

TEST(constructors, test_size_fill_dbl)
{
    Matrix<double> a(3, 5, 5.23);

    EXPECT_EQ(a.getNRows(), 3);
    EXPECT_EQ(a.getNCols(), 5);

    EXPECT_EQ(a.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());

    EXPECT_NO_THROW(a(1, 2));

    for (auto elem : a)
        EXPECT_EQ(elem, 5.23);

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), 5.23);
}

TEST(constructors, test_from_dynamic_arr)
{
    size_t n_rows = 2;
    size_t n_cols = 3;
    int src[2][3] = {{0, 5, 34}, {2, 4, 6}};

    int **src_dyn = new int *[n_rows];
    for (size_t i = 0; i < n_rows; ++i) {
        src_dyn[i] = new int[n_cols];
        memcpy(src_dyn[i], src[i], sizeof(int) * n_cols);
    }

    Matrix<int> a((const int **)src_dyn, n_rows, n_cols);

    EXPECT_EQ(a.getNRows(), 2);
    EXPECT_EQ(a.getNCols(), 3);

    EXPECT_EQ(a.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());

    EXPECT_NO_THROW(a(1, 2));

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), src[i][j]);

    for (size_t i = 0; i < n_rows; ++i)
        delete[] src_dyn[i];
    delete[] src_dyn;
}

TEST(constructors, test_from_part_dynamic_arr)
{
    size_t n_rows = 2;
    size_t n_cols = 3;
    int src[2][3] = {{0, 5, 34}, {2, 4, 6}};

    int **src_dyn = new int *[n_rows];
    for (size_t i = 0; i < n_rows; ++i) {
        src_dyn[i] = new int[n_cols];
        memcpy(src_dyn[i], src[i], sizeof(int) * n_cols);
    }

    Matrix<int> a((const int **)src_dyn, 2, 2);

    EXPECT_EQ(a.getNRows(), 2);
    EXPECT_EQ(a.getNCols(), 2);

    EXPECT_EQ(a.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());

    EXPECT_NO_THROW(a(1, 0));

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), src[i][j]);

    for (size_t i = 0; i < n_rows; ++i)
        delete[] src_dyn[i];
    delete[] src_dyn;
}

TEST(constructors, test_from_arr)
{
    int src[2][3] = {{0, 5, 34}, {2, 4, 6}};
    Matrix<int> a = {{0, 5, 34}, {2, 4, 6}};

    EXPECT_EQ(a.getNRows(), 2);
    EXPECT_EQ(a.getNCols(), 3);

    EXPECT_EQ(a.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());

    EXPECT_NO_THROW(a(1, 0));

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), src[i][j]);
}

TEST(constructors, test_copy)
{
    Matrix<int> a({{0, 5, 34}, {234, 34, 4}});
    Matrix<int> b(a);

    EXPECT_EQ(a.getNRows(), b.getNRows());
    EXPECT_EQ(a.getNCols(), b.getNCols());

    EXPECT_EQ(a.isEmpty(), false);
    EXPECT_EQ(b.isEmpty(), false);

    EXPECT_NE(a.begin(), a.end());
    EXPECT_NE(b.begin(), b.end());

    EXPECT_NO_THROW(b(1, 0));

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), b(i, j));
}

TEST(constructors, test_move)
{
    int src[2][3] = {{0, 5, 34}, {2, 4, 6}};
    Matrix<int> a({{0, 5, 34}, {2, 4, 6}});
    Matrix<int> b(std::move(a));

    EXPECT_EQ(b.getNRows(), 2);
    EXPECT_EQ(b.getNCols(), 3);
    EXPECT_EQ(b.isEmpty(), false);
    EXPECT_NE(b.begin(), b.end());
    EXPECT_NO_THROW(b(1, 0));

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(b(i, j), src[i][j]);
}

#endif // TEST_CONSTRUCTORS_INL
