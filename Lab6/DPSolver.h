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
    long long recursiveDP(int i, int j);

    const Vector<int>& dims_;
    int n_{};
    long long bestCost_{};
    TDVector<long long> dp_;
    TDVector<int> split_;
};