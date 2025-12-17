#pragma once

#include "IMatrixChainSolver.h"
#include "MatrixChain.h"

class DPSolver final : public IMatrixChainSolver {

    template<class T>
    using TDVector = Vector<Vector<T>>;

public:
    explicit DPSolver(const MatrixChain& chain);
    long long solve() override;
    [[nodiscard]] std::string getExpression() const override;

private:
    [[nodiscard]] std::string buildExpression(int i, int j) const;

    const Vector<int>& p_;
    int n_{};
    long long best_cost_{};
    TDVector<long long> dp_;
    TDVector<int> split_;
};