#include "array.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: Lab1CPPMonthly INPUT_FILE\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    int count = 0;
    if (!(input >> count) || (count != 365 && count != 366))
    {
        std::cerr << "Expected 365 or 366 days\n";
        return 1;
    }

    Array<double> rain(static_cast<std::size_t>(count));
    for (std::size_t i = 0; i < rain.size(); ++i)
    {
        double value = 0;
        if (!(input >> value) || !std::isfinite(value) || value < 0)
        {
            std::cerr << "Invalid precipitation value\n";
            return 1;
        }
        rain.set(i, value);
    }

    const int month_days[12] =
        {31, count == 366 ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Array<double> totals(12);
    std::size_t day = 0;
    for (std::size_t month = 0; month < totals.size(); ++month)
    {
        double sum = 0;
        for (int i = 0; i < month_days[month]; ++i)
            sum += rain.get(day++);

        if (!std::isfinite(sum))
        {
            std::cerr << "Monthly total is too large\n";
            return 1;
        }
        totals.set(month, sum);
    }

    std::cout << std::setprecision(15);
    for (std::size_t month = 0; month < totals.size(); ++month)
    {
        if (month != 0)
            std::cout << ' ';
        std::cout << totals.get(month);
    }
    std::cout << '\n';
    return 0;
}
