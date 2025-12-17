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

    best_cost_ = std::numeric_limits<long long>::max();
    best_expr_ = "";

    recursiveSearch(0, n_ - 1);

    return best_cost_;
}

[[nodiscard]] std::string ExhaustiveSolver::getExpression() const {
    return stripOuterParentheses(best_expr_);
}

std::pair<long long, std::string> ExhaustiveSolver::recursiveSearch(const int i, const int j) {
    if (i == j) {
        return {0, std::to_string(dims_[i]) + "x" + std::to_string(dims_[i + 1])};
    }

    long long min_cost = std::numeric_limits<long long>::max();
    std::string best_expr;

    for (int k = i; k < j; ++k) {
        auto [left_cost, left_expr] = recursiveSearch(i, k);
        auto [right_cost, right_expr] = recursiveSearch(k + 1, j);

        const long long current_cost = left_cost + right_cost +
            static_cast<long long>(dims_[i]) * dims_[k + 1] * dims_[j + 1];

        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_expr = "(" + left_expr + "*" + right_expr + ")";
        }
    }

    if (i == 0 && j == n_ - 1) {
        best_cost_ = min_cost;
        best_expr_ = best_expr;
    }

    return {min_cost, best_expr};
}