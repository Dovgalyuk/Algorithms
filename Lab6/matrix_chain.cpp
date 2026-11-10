#include "matrix_chain.h"

#include <limits>
#include <sstream>
#include <stdexcept>

using namespace std;

Dimensions readDimensions(istream& input)
{
    if (input.peek() == 0xEF)
    {
        input.get();
        if (input.get() != 0xBB || input.get() != 0xBF)
            throw invalid_argument(u8"Неверная кодировка входного файла.");
    }

    Dimensions dimensions;
    while (true)
    {
        input >> ws;
        if (input.bad())
            throw runtime_error(u8"Ошибка чтения входного файла.");
        if (input.eof())
            break;

        long long rows, columns;
        if (!(input >> rows >> columns))
            throw invalid_argument(u8"Ожидаются пары целых размерностей матриц.");
        if (rows <= 0 || columns <= 0)
            throw invalid_argument(u8"Размерности матриц должны быть положительными.");
        if (dimensions.empty())
            dimensions.push_back(rows);
        else if (dimensions.back() != rows)
            throw invalid_argument(u8"Размерности соседних матриц несовместимы.");
        dimensions.push_back(columns);
    }

    if (dimensions.empty())
        throw invalid_argument(u8"Входной файл не содержит матриц.");
    return dimensions;
}

static void validate(const Dimensions& dimensions)
{
    if (dimensions.size() < 2)
        throw invalid_argument(u8"Нужна хотя бы одна матрица.");
    for (long long dimension : dimensions)
        if (dimension <= 0)
            throw invalid_argument(u8"Размерности матриц должны быть положительными.");
}

static long long combine(long long left, long long right,
                         long long rows, long long middle, long long columns)
{
    const long long maximum = numeric_limits<long long>::max();
    if (left < 0 || right < 0 || rows > maximum / middle)
        return -1;
    long long product = rows * middle;
    if (product > maximum / columns)
        return -1;
    product *= columns;
    if (left > maximum - right)
        return -1;
    long long sum = left + right;
    if (sum > maximum - product)
        return -1;
    return sum + product;
}

static long long bruteForce(const Dimensions& dimensions, size_t left, size_t right,
                            vector<vector<size_t>>& split)
{
    if (left == right)
        return 0;

    long long best = -1;
    for (size_t k = left; k < right; ++k)
    {
        long long first = bruteForce(dimensions, left, k, split);
        long long second = bruteForce(dimensions, k + 1, right, split);
        long long cost = combine(first, second, dimensions[left],
                                 dimensions[k + 1], dimensions[right + 1]);
        if (cost >= 0 && (best < 0 || cost < best))
        {
            best = cost;
            split[left][right] = k;
        }
    }
    return best;
}

Result solveBruteForce(const Dimensions& dimensions)
{
    validate(dimensions);
    size_t n = dimensions.size() - 1;
    Result result{0, vector<vector<size_t>>(n, vector<size_t>(n))};
    result.cost = bruteForce(dimensions, 0, n - 1, result.split);
    if (result.cost < 0)
        throw overflow_error(u8"Минимальная стоимость не помещается в long long.");
    return result;
}

Result solveDynamic(const Dimensions& dimensions)
{
    validate(dimensions);
    size_t n = dimensions.size() - 1;
    Result result{0, vector<vector<size_t>>(n, vector<size_t>(n))};
    vector<vector<long long>> cost(n, vector<long long>(n, -1));
    for (size_t i = 0; i < n; ++i)
        cost[i][i] = 0;

    for (size_t length = 2; length <= n; ++length)
    {
        for (size_t left = 0; left <= n - length; ++left)
        {
            size_t right = left + length - 1;
            for (size_t k = left; k < right; ++k)
            {
                long long candidate = combine(cost[left][k], cost[k + 1][right],
                                               dimensions[left], dimensions[k + 1],
                                               dimensions[right + 1]);
                if (candidate >= 0 && (cost[left][right] < 0 || candidate < cost[left][right]))
                {
                    cost[left][right] = candidate;
                    result.split[left][right] = k;
                }
            }
        }
    }

    result.cost = cost[0][n - 1];
    if (result.cost < 0)
        throw overflow_error(u8"Минимальная стоимость не помещается в long long.");
    return result;
}

static void writeProduct(ostream& output, const Dimensions& dimensions,
                         const vector<vector<size_t>>& split,
                         size_t left, size_t right, bool brackets)
{
    if (left == right)
    {
        output << dimensions[left] << 'x' << dimensions[left + 1];
        return;
    }

    if (brackets)
        output << '(';
    size_t middle = split[left][right];
    writeProduct(output, dimensions, split, left, middle, true);
    output << '*';
    writeProduct(output, dimensions, split, middle + 1, right, true);
    if (brackets)
        output << ')';
}

string parenthesize(const Dimensions& dimensions, const Result& result)
{
    ostringstream output;
    writeProduct(output, dimensions, result.split, 0, dimensions.size() - 2, false);
    return output.str();
}
