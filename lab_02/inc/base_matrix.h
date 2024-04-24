#ifndef BASE_MATRIX_H
#define BASE_MATRIX_H
#include <cstddef>

class BaseMatrix
{
public:
    BaseMatrix() noexcept;
    BaseMatrix(const size_t n_rows, const size_t n_cols) noexcept;

    size_t getNCols() const noexcept;
    size_t getNRows() const noexcept;

    bool isEmpty() const noexcept;

    // TODO(Talkasi): Check this line.
    virtual ~BaseMatrix() = 0;

protected:
    size_t nRows = 0;
    size_t nCols = 0;
};

#endif // BASE_MATRIX_H
