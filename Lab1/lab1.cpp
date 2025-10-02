#include "array.h"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>

using IntArray = Array<int>;

static IntArray createArrayFromSize(std::istream& input)
{
    int size = 0;
    if (!(input >> size) || size < 0)
    {
        throw std::runtime_error("Fail to read");
    }

    return IntArray(static_cast<size_t>(size));
}

static void fillArrayFromStream(IntArray& array, std::istream& input)
{
    for (size_t i = 0; i < array.size(); ++i)
    {
        int value = 0;
        if (!(input >> value))
        {
            throw std::runtime_error("Fail to read");
        }
        array.set(i, value);
    }
}

static void task1(IntArray& array)
{
    int remainder = 1 % 17;
    for (size_t i = 0; i < array.size(); ++i)
    {
        remainder *= 10;
        int digit = remainder / 17;
        remainder %= 17;
        array.set(i, digit);
    }

    for (size_t i = 0; i < array.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << ' ';
        }
        std::cout << array.get(i);
    }
}

static void task2(const IntArray& array)
{
    bool answer = false;
    int minDiff = 0;

    for (size_t i = 0; i < array.size(); ++i)
    {
        int valI = array.get(i);
        if (valI % 2 != 0)
        {
            continue;
        }

        for (size_t j = i + 1; j < array.size(); ++j)
        {
            int valJ = array.get(j);
            if (valJ % 2 != 0 || valJ == valI)
            {
                continue;
            }

            int diff = valI - valJ;
            if (diff < 0)
            {
                diff = -diff;
            }

            if (!answer || diff < minDiff)
            {
                minDiff = diff;
                answer = true;
            }
        }
    }

    if (answer)
    {
        std::cout << minDiff << '\n';
    }
    else
    {
        std::cout << "no\n";
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Fail to open file\n";
        return 1;
    }

    try
    {
        IntArray digits = createArrayFromSize(input);
        task1(digits);

        if (digits.size() > 0)
        {
            std::cout << ' ';
        }

        IntArray numbers = createArrayFromSize(input);
        fillArrayFromStream(numbers, input);
        std::cout << '\n';
        task2(numbers);
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}