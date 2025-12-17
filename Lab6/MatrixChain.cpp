#include "MatrixChain.h"

MatrixChain::MatrixChain(const Matrix& matrices) {
    if (matrices.empty()) {
        throw std::runtime_error("Empty matrix chain");
    }

    for (const auto& [rows, cols] : matrices) {
        if (rows <= 0 || cols <= 0) {
            throw std::runtime_error("Matrix dimensions must be positive");
        }
        if (rows > MAX_MATRIX_SIZE || cols > MAX_MATRIX_SIZE) {
            throw std::runtime_error("Matrix dimensions too large");
        }
    }

    dims_.reserve(matrices.size() + 1);
    dims_.push_back(matrices[0].first);

    for (auto i{ 0 }; i < matrices.size(); ++i) {
        dims_.push_back(matrices[i].second);

        if (i > 0 && matrices[i - 1].second != matrices[i].first) {
            throw std::runtime_error("Incompatible matrix dimensions");
        }
    }

    if (matrices.size() > MAX_CHAIN_SIZE) {
        throw std::runtime_error("Matrix chain too long");
    }
}

[[nodiscard]] const Vector<int>& MatrixChain::dims() const {
    return dims_;
}

[[nodiscard]] int MatrixChain::size() const {
    return static_cast<int>(dims_.size()) - 1;
}