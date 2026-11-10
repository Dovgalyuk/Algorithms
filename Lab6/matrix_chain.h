#ifndef MATRIX_CHAIN_H
#define MATRIX_CHAIN_H

#include <cstddef>
#include <istream>
#include <string>
#include <vector>

using Dimensions = std::vector<long long>;

struct Result
{
    long long cost;
    std::vector<std::vector<std::size_t>> split;
};

Dimensions readDimensions(std::istream& input);
Result solveBruteForce(const Dimensions& dimensions);
Result solveDynamic(const Dimensions& dimensions);
std::string parenthesize(const Dimensions& dimensions, const Result& result);
int runProgram(int argc, char* argv[], bool dynamic);

#endif
