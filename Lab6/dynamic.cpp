#include "matrix_chain.h"

#include <stdexcept>

using namespace std;

namespace dynamic_programming
{
static const long long NOT_COMPUTED = -2;

static long long solveRange(const Dimensions& dimensions, size_t left, size_t right,
                            vector<vector<size_t>>& split,
                            vector<vector<long long>>& saved)
{
    if (left == right)
        return 0;
    if (saved[left][right] != NOT_COMPUTED)
        return saved[left][right];

    long long best = -1;
    for (size_t k = left; k < right; ++k)
    {
        long long first = solveRange(dimensions, left, k, split, saved);
        long long second = solveRange(dimensions, k + 1, right, split, saved);
        long long cost = matrix_chain_detail::combine(
            first, second, dimensions[left], dimensions[k + 1], dimensions[right + 1]);
        if (cost >= 0 && (best < 0 || cost < best))
        {
            best = cost;
            split[left][right] = k;
        }
    }
    saved[left][right] = best;
    return best;
}

Result solve(const Dimensions& dimensions)
{
    matrix_chain_detail::validate(dimensions);
    size_t n = dimensions.size() - 1;
    Result result;
    result.split.resize(n, vector<size_t>(n));
    vector<vector<long long>> saved(n, vector<long long>(n, NOT_COMPUTED));
    result.cost = solveRange(dimensions, 0, n - 1, result.split, saved);
    if (result.cost < 0)
        throw overflow_error(u8"Минимальная стоимость не помещается в long long.");
    return result;
}
}
