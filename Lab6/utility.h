#pragma once

#include <chrono>
#include <string>

#include "vector.h"

using Clock = std::chrono::steady_clock;
using ms = std::chrono::duration<double, std::milli>;
using ns = std::chrono::duration<double, std::nano>;

constexpr int MAX_MATRIX_SIZE = 10000;
constexpr int MAX_CHAIN_SIZE = 100;

using Matrix = Vector<std::pair<int, int>>;

std::string stripOuterParentheses(const std::string& s);
Matrix readMatrices(std::istream& in);
