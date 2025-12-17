#pragma once
#include <stdexcept>
#include "utility.h"
#include "vector.h"

class MatrixChain {
public:
    explicit MatrixChain(const Matrix& matrices);

    [[nodiscard]] const Vector<int>& dims() const;
    [[nodiscard]] int size() const;
private:
    Vector<int> dims_;
};
