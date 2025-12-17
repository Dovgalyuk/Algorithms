#include "utility.h"

std::string stripOuterParentheses(const std::string& s) {
    if (s.size() < 2 || s.front() != '(' || s.back() != ')')
        return s;

    int balance{};
    for (auto i{ 0 }; i < s.size(); ++i) {
        if (s[i] == '(') {
            ++balance;
        } else if (s[i] == ')') {
            --balance;
            if (balance == 0) {
                if (i != s.size() - 1) {
                    return s;
                }
                break;
            }
        }
    }
    return s.substr(1, s.size() - 2);
}

Matrix readMatrices(std::istream& in) {
    Matrix matrices;
    int rows, cols;

    while (in >> rows >> cols) {
        if (!in) {
            throw std::runtime_error("Invalid input format");
        }
        matrices.emplace_back(rows, cols);
    }

    if (matrices.empty()) {
        throw std::runtime_error("No matrices provided");
    }

    return matrices;
}