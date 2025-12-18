#include "DPSolver.h"

DPSolver::DPSolver(const MatrixChain &chain)
    : dims_(chain.dims()),
      n_(chain.size()),
      split_(n_, Vector<int>(n_, -1)) {
    dp_.resize(n_, Vector<long long>(n_, -1));
}

long long DPSolver::solve() {
    bestCost_ = recursiveDP(0, n_ - 1);
    return bestCost_;
}

long long DPSolver::recursiveDP(const int i, const int j) {
    if (i == j) {
        return 0;
    }

    if (dp_[i][j] != -1) {
        return dp_[i][j];
    }

    long long minCost = std::numeric_limits<long long>::max();
    int bestSplit = -1;

    for (auto k{i}; k < j; ++k) {
        const auto leftCost = recursiveDP(i, k);
        const auto rightCost = recursiveDP(k + 1, j);

        const auto currentCost = leftCost + rightCost +
                                 static_cast<long long>(dims_[i]) * dims_[k + 1] * dims_[j + 1];

        if (currentCost < minCost) {
            minCost = currentCost;
            bestSplit = k;
        }
    }

    dp_[i][j] = minCost;
    split_[i][j] = bestSplit;

    return minCost;
}

[[nodiscard]] std::string DPSolver::getExpression() const {
    return buildExpression(0, n_ - 1);
}

std::string DPSolver::buildExpression(const int i, const int j) const {
    if (i == j) {
        return std::to_string(dims_[i]) + "x" + std::to_string(dims_[i + 1]);
    }

    const auto k = split_[i][j];

    const std::string left = buildExpression(i, k);
    const std::string right = buildExpression(k + 1, j);

    if (i == 0 && j == n_ - 1) {
        return left + "*" + right;
    }
    return "(" + left + "*" + right + ")";
}
