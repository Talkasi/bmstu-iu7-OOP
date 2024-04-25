#include "matrix_tests.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "Russian");

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
