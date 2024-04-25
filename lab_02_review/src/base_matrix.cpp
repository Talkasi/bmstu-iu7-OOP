#include "base_matrix.h"

BaseMatrix::BaseMatrix() noexcept
{
    n_rows = 0;
    n_cols = 0;
}

BaseMatrix::BaseMatrix(const size_t n_rows, const size_t n_cols) noexcept : n_rows(n_rows), n_cols(n_cols){};

BaseMatrix::~BaseMatrix() = default;

bool BaseMatrix::isEmpty() const noexcept
{
    return n_rows == 0 || n_cols == 0;
}

size_t BaseMatrix::getNRows() const noexcept
{
    return n_rows;
}

size_t BaseMatrix::getNCols() const noexcept
{
    return n_cols;
}

bool BaseMatrix::isSquare() const noexcept
{
    if (n_rows != n_cols)
        return false;

    return true;
}
