#ifndef MATRIX_CHAIN_H
#define MATRIX_CHAIN_H

#include <cstddef>
#include <istream>
#include <string>
#include <vector>

typedef std::vector<long long> Dimensions;

struct Result
{
    long long cost;
    std::vector<std::vector<std::size_t>> split;
};

Dimensions readDimensions(std::istream& input);
Result solve(const Dimensions& dimensions);
void validateDimensions(const Dimensions& dimensions);
long long combineCosts(long long left, long long right,
                       long long rows, long long middle, long long columns);
std::string parenthesize(const Dimensions& dimensions, const Result& result);

#endif
