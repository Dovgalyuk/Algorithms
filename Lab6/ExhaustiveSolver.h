#pragma once
#include <limits>
#include <string>

#include "IMatrixChainSolver.h"
#include "MatrixChain.h"
#include "vector.h"

class ExhaustiveSolver final : public IMatrixChainSolver {
public:
    explicit ExhaustiveSolver(const MatrixChain& chain);

    long long solve() override;
    [[nodiscard]] std::string getExpression() const override;

private:
    std::pair<long long, std::string> recursiveSearch(int i, int j);

    const Vector<int>& dims_;
    int n_;
    long long bestCost_{};
    std::string bestExpr_{};
};
