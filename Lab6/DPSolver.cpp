#include "DPSolver.h"

DPSolver::DPSolver(const MatrixChain& chain)
        : p_(chain.dims()),
          n_(chain.size()),
          split_(n_, Vector<int>(n_, -1)) {
    dp_.resize(n_, Vector<long long>(n_, std::numeric_limits<long long>::max()));
}

long long DPSolver::solve() {
    for (int i = 0; i < n_; ++i) {
        dp_[i][i] = 0;
    }

    for (int len = 2; len <= n_; ++len) {
        for (int i = 0; i <= n_ - len; ++i) {
            const int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                const long long cost = dp_[i][k] + dp_[k + 1][j]
                    + static_cast<long long>(p_[i]) * p_[k + 1] * p_[j + 1];

                if (cost < dp_[i][j]) {
                    dp_[i][j] = cost;
                    split_[i][j] = k;
                }
            }
        }
    }

    best_cost_ = dp_[0][n_ - 1];
    return best_cost_;
}

[[nodiscard]] std::string DPSolver::getExpression() const {
    return buildExpression(0, n_ - 1);
}

std::string DPSolver::buildExpression(const int i, const int j) const {
    if (i == j) {
        return std::to_string(p_[i]) + "x" + std::to_string(p_[i + 1]);
    }

    const auto k = split_[i][j];

    const std::string left  = buildExpression(i, k);
    const std::string right = buildExpression(k + 1, j);

    if (i == 0 && j == n_ - 1) {
        return left + "*" + right;
    }
    return "(" + left + "*" + right + ")";
}