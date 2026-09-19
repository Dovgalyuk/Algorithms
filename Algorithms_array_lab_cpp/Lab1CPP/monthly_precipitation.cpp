#include "array.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: Lab1CPPMonthly INPUT_FILE\n";
        return 2;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    std::size_t days = 0;
    if (!(input >> days) || (days != 365 && days != 366))
    {
        std::cerr << "The input array must contain 365 or 366 values\n";
        return 1;
    }

    Array<long long> precipitation(days);
    for (std::size_t i = 0; i < days; ++i)
    {
        long long value = 0;
        if (!(input >> value))
        {
            std::cerr << "Not enough precipitation values\n";
            return 1;
        }
        precipitation.set(i, value);
    }

    std::size_t month_lengths[12] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (days == 366)
        month_lengths[1] = 29;

    Array<long long> monthly_totals(12);
    std::size_t day = 0;
    for (std::size_t month = 0; month < 12; ++month)
    {
        for (std::size_t day_in_month = 0;
             day_in_month < month_lengths[month]; ++day_in_month)
        {
            monthly_totals.set(month,
                monthly_totals.get(month) + precipitation.get(day));
            ++day;
        }
    }

    for (std::size_t month = 0; month < 12; ++month)
    {
        if (month != 0)
            std::cout << ' ';
        std::cout << monthly_totals.get(month);
    }
    std::cout << '\n';
    return 0;
}