#ifndef TEST_ASSIGNMENT_INL
#define TEST_ASSIGNMENT_INL
#include "matrix.h"
#include <gtest/gtest.h>
#include <ranges>

TEST(assignment, test_assign_init_list)
{
    int expected[2][3] = {{1, 2, 3}, {4, 5, 6}};
    Matrix<int> a;
    a = {{1, 2, 3}, {4, 5, 6}};

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), expected[i][j]);
}

TEST(assignment, test_assign_copy)
{
    Matrix<int> a;
    Matrix<int> b({{1, 2, 3}, {4, 5, 6}});

    a = b;

    EXPECT_EQ(a.getNRows(), 2);
    EXPECT_EQ(a.getNCols(), 3);

    EXPECT_EQ(b.getNRows(), 2);
    EXPECT_EQ(b.getNCols(), 3);

    EXPECT_EQ(a.isEmpty(), false);
    EXPECT_EQ(b.isEmpty(), false);

    for (size_t i = 0; i < a.getNRows(); ++i)
        for (size_t j = 0; j < a.getNCols(); ++j)
            EXPECT_EQ(a(i, j), b(i, j));
}

#endif