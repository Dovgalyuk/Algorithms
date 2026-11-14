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
namespace brute_force
{
Result solve(const Dimensions& dimensions);
}
namespace dynamic_programming
{
Result solve(const Dimensions& dimensions);
}
namespace matrix_chain_detail
{
void validate(const Dimensions& dimensions);
long long combine(long long left, long long right,
                  long long rows, long long middle, long long columns);
}
std::string parenthesize(const Dimensions& dimensions, const Result& result);

#endif
