#include "ExhaustiveSolver.h"

ExhaustiveSolver::ExhaustiveSolver(const MatrixChain& chain) : dims_(chain.dims()), n_(chain.size()) {
    if (n_ > 20) {
        throw std::runtime_error("Recursive exhaustive search only works for n <= 20");
    }
}

long long ExhaustiveSolver::solve() {
    if (n_ <= 1) {
        return 0;
    }

    recursiveSearch(0, n_ - 1);

    return bestCost_;
}

[[nodiscard]] std::string ExhaustiveSolver::getExpression() const {
    return stripOuterParentheses(bestExpr_);
}

std::pair<long long, std::string> ExhaustiveSolver::recursiveSearch(const int i, const int j) {
    if (i == j) {
        return {0, std::to_string(dims_[i]) + "x" + std::to_string(dims_[i + 1])};
    }

    long long minCost = std::numeric_limits<long long>::max();
    std::string bestExpr;

    for (auto k{ i }; k < j; ++k) {
        auto [leftCost, leftExpr] = recursiveSearch(i, k);
        auto [rightCost, rightExpr] = recursiveSearch(k + 1, j);

        const long long currentСost = leftCost + rightCost +
            static_cast<long long>(dims_[i]) * dims_[k + 1] * dims_[j + 1];

        if (currentСost < minCost) {
            minCost = currentСost;
            bestExpr = "(" + leftExpr + "*" + rightExpr + ")";
        }
    }

    if (i == 0 && j == n_ - 1) {
        bestCost_ = minCost;
        bestExpr_ = bestExpr;
    }

    return {minCost, bestExpr};
}