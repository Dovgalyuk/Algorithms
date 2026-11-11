#include "matrix_chain.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

static int checks = 0;

static void require(bool condition, const string& message)
{
    ++checks;
    if (!condition)
        throw runtime_error(message);
}

static long long multiply(long long a, long long b)
{
    require(a >= 0 && b > 0, "Invalid multiplication in output");
    require(a <= numeric_limits<long long>::max() / b, "Overflow in output");
    return a * b;
}

static long long add(long long a, long long b)
{
    require(a >= 0 && b >= 0, "Negative cost in output");
    require(a <= numeric_limits<long long>::max() - b, "Cost overflow in output");
    return a + b;
}

struct ParsedProduct
{
    long long rows;
    long long columns;
    long long cost;
};

class ExpressionParser
{
    const string& expression;
    const Dimensions& dimensions;
    size_t position = 0;
    size_t matrix = 0;

    long long number()
    {
        require(position < expression.size() &&
                isdigit(static_cast<unsigned char>(expression[position])),
                "Expected a matrix dimension");
        long long value = 0;
        while (position < expression.size() &&
               isdigit(static_cast<unsigned char>(expression[position])))
        {
            const int digit = expression[position++] - '0';
            require(value <= (numeric_limits<long long>::max() - digit) / 10,
                    "Dimension overflow in output");
            value = value * 10 + digit;
        }
        return value;
    }

    ParsedProduct factor()
    {
        require(position < expression.size(), "Unexpected end of expression");
        if (expression[position] == '(')
        {
            ++position;
            const ParsedProduct product = productExpression();
            require(position < expression.size() && expression[position] == ')',
                    "Missing closing parenthesis");
            ++position;
            return product;
        }
        const long long rows = number();
        require(position < expression.size() && expression[position] == 'x',
                "Missing x between dimensions");
        ++position;
        const long long columns = number();
        require(matrix + 1 < dimensions.size(), "Too many matrices in output");
        require(rows == dimensions[matrix] && columns == dimensions[matrix + 1],
                "Matrix order or dimensions changed");
        ++matrix;
        return {rows, columns, 0};
    }

    ParsedProduct productExpression()
    {
        ParsedProduct left = factor();
        while (position < expression.size() && expression[position] == '*')
        {
            ++position;
            const ParsedProduct right = factor();
            require(left.columns == right.rows, "Incompatible matrices in output");
            const long long operationCost = multiply(multiply(left.rows, left.columns),
                                                     right.columns);
            left.cost = add(add(left.cost, right.cost), operationCost);
            left.columns = right.columns;
        }
        return left;
    }

public:
    ExpressionParser(const string& text, const Dimensions& values)
        : expression(text), dimensions(values)
    {
    }

    long long evaluate()
    {
        const ParsedProduct product = productExpression();
        require(position == expression.size(), "Unexpected characters in output");
        require(matrix + 1 == dimensions.size(), "Missing matrices in output");
        require(product.rows == dimensions.front() &&
                product.columns == dimensions.back(), "Wrong result dimensions");
        return product.cost;
    }
};

static vector<long long> enumerateCosts(const Dimensions& dimensions, size_t first,
                                      size_t last)
{
    if (first == last)
        return {0};
    vector<long long> costs;
    for (size_t split = first; split < last; ++split)
    {
        const vector<long long> left = enumerateCosts(dimensions, first, split);
        const vector<long long> right = enumerateCosts(dimensions, split + 1, last);
        for (long long leftCost : left)
            for (long long rightCost : right)
                costs.push_back(leftCost + rightCost + dimensions[first] *
                                dimensions[split + 1] * dimensions[last + 1]);
    }
    return costs;
}

static void checkResult(const Dimensions& dimensions, const Result& result,
                        long long expected)
{
    require(result.cost == expected, "Wrong minimum multiplication count");
    const string expression = parenthesize(dimensions, result);
    ExpressionParser parser(expression, dimensions);
    require(parser.evaluate() == expected, "Parentheses do not match minimum cost");
}

static void checkBoth(const Dimensions& dimensions, long long expected)
{
    checkResult(dimensions, solveBruteForce(dimensions), expected);
    checkResult(dimensions, solveDynamic(dimensions), expected);
}

template<class Exception, class Function>
static void expectException(Function function, const string& message)
{
    bool caught = false;
    try
    {
        function();
    }
    catch (const Exception&)
    {
        caught = true;
    }
    require(caught, message);
}

static void testInput()
{
    istringstream sample("10 30\n30 5\n5 60\n");
    require(readDimensions(sample) == Dimensions({10, 30, 5, 60}), "Sample input failed");
    istringstream whitespace(" \t\r\n10\t30  \r\n30 5\n\n5 60\t");
    require(readDimensions(whitespace) == Dimensions({10, 30, 5, 60}),
            "Whitespace handling failed");
    istringstream noNewline("7 9");
    require(readDimensions(noNewline) == Dimensions({7, 9}), "Missing final newline failed");
    istringstream utf8Bom("\xEF\xBB\xBF" "10 30\n30 5\n5 60\n");
    require(readDimensions(utf8Bom) == Dimensions({10, 30, 5, 60}), "UTF-8 BOM failed");
    istringstream large("9223372036854775807 1");
    require(readDimensions(large) == Dimensions({numeric_limits<long long>::max(), 1}),
            "Maximum dimension failed");

    const vector<string> invalid = {
        "", " \r\n\t", "10", "10 30 5", "10 30\n20 5", "0 5", "5 0",
        "-1 5", "5 -1", "a 5", "10 30 a b", "10 30 30 x", "10.5 30",
        "10 30 30 5!", "9223372036854775808 1", "10 30 30 9223372036854775808",
        "\xEF", "\xEF\xBB", "\xEF\xBA\xBF" "10 30"
    };
    for (const string& text : invalid)
    {
        expectException<exception>([&text]() {
            istringstream input(text);
            readDimensions(input);
        }, "Invalid input accepted: " + text);
    }
}

static void testKnownAnswers()
{
    const Dimensions sample = {10, 30, 5, 60};
    checkBoth(sample, 4500);
    require(parenthesize(sample, solveBruteForce(sample)) == "(10x30*30x5)*5x60",
            "Brute force sample format differs");
    require(parenthesize(sample, solveDynamic(sample)) == "(10x30*30x5)*5x60",
            "Dynamic sample format differs");
    checkBoth({7, 9}, 0);
    require(parenthesize({7, 9}, solveDynamic({7, 9})) == "7x9", "Single matrix format");
    checkBoth({10, 20, 30}, 6000);
    require(parenthesize({10, 20, 30}, solveDynamic({10, 20, 30})) == "10x20*20x30",
            "Two matrix format");
    checkBoth({30, 35, 15, 5, 10, 20, 25}, 15125);
    checkBoth({5, 10, 3, 12, 5, 50, 6}, 2010);
    checkBoth({2, 2, 2, 2, 2}, 24);
    checkBoth({1, 1, 1, 1, 1, 1, 1, 1}, 6);
    checkBoth({100000, 100000, 100000}, 1000000000000000LL);
    checkBoth({10000000, 10000000, 1, 10000000}, 200000000000000LL);
    checkBoth({10000000, 1, 10000000, 10000000}, 200000000000000LL);
    checkBoth({numeric_limits<long long>::max(), 1}, 0);
    checkBoth({numeric_limits<long long>::max(), 1, 1}, numeric_limits<long long>::max());
    checkBoth({1, numeric_limits<long long>::max(), 1}, numeric_limits<long long>::max());
}

static void testErrors()
{
    const vector<Dimensions> invalid = {{}, {10}, {0, 5}, {5, -1}, {5, 0, 5}};
    for (const Dimensions& dimensions : invalid)
    {
        expectException<invalid_argument>([&dimensions]() { solveBruteForce(dimensions); },
                                          "Brute force accepted invalid dimensions");
        expectException<invalid_argument>([&dimensions]() { solveDynamic(dimensions); },
                                          "Dynamic accepted invalid dimensions");
    }
    const vector<Dimensions> overflow = {
        {numeric_limits<long long>::max(), 2, 1},
        {3000000, 3000000, 3000000},
        {2000000, 2000000, 2000000, 2000000},
        {1000000000000LL, 1, 1000000, 1, 10000000}
    };
    for (const Dimensions& dimensions : overflow)
    {
        expectException<overflow_error>([&dimensions]() { solveBruteForce(dimensions); },
                                        "Brute force did not detect overflow");
        expectException<overflow_error>([&dimensions]() { solveDynamic(dimensions); },
                                        "Dynamic did not detect overflow");
    }
    const Dimensions largeOverflow(101, 3000000);
    expectException<overflow_error>([&largeOverflow]() { solveDynamic(largeOverflow); },
                                    "Dynamic did not cache overflowing subproblems");
}

static void testRandomChains()
{
    mt19937 generator(188906);
    uniform_int_distribution<int> value(1, 30);
    for (size_t count = 1; count <= 8; ++count)
    {
        for (int test = 0; test < 25; ++test)
        {
            Dimensions dimensions(count + 1);
            for (long long& dimension : dimensions)
                dimension = value(generator);
            const vector<long long> allCosts = enumerateCosts(dimensions, 0, count - 1);
            const long long minimum = *min_element(allCosts.begin(), allCosts.end());
            checkBoth(dimensions, minimum);
        }
    }
    const Dimensions large(401, 1);
    checkResult(large, solveDynamic(large), 399);
}

int main()
{
    try
    {
        testInput();
        testKnownAnswers();
        testErrors();
        testRandomChains();
        cout << "All matrix chain tests passed: " << checks << " checks\n";
        return 0;
    }
    catch (const exception& error)
    {
        cerr << "Test failed: " << error.what() << '\n';
        return 1;
    }
}
