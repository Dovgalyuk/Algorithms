#pragma once

#include <string>

class IMatrixChainSolver {
public:
    virtual ~IMatrixChainSolver() = default;
    virtual long long solve() = 0;
    [[nodiscard]] virtual std::string getExpression() const = 0;
};
