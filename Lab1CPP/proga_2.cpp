#include "array.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: Lab1CPPMonthly INPUT_FILE\n";
        return 2;
    }

    ifstream input(argv[1]);
    if (!input)
    {
        cout << "Cannot open input file\n";
        return 1;
    }

    size_t days = 0;
    if (!(input >> days) || (days != 365 && days != 366))
    {
        cout << "The input array must contain 365 or 366 values\n";
        return 1;
    }

    Array<long long> precipitation(days);
    for (size_t i = 0; i < days; ++i)
    {
        long long value = 0;
        if (!(input >> value))
        {
            cout << "Not enough precipitation values\n";
            return 1;
        }
        precipitation.set(i, value);
    }

    size_t month_lengths[12] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (days == 366)
        month_lengths[1] = 29;

    Array<long long> monthly_totals(12);
    size_t day = 0;
    for (size_t month = 0; month < 12; ++month)
    {
        for (size_t day_in_month = 0;
             day_in_month < month_lengths[month]; ++day_in_month)
        {
            monthly_totals.set(month,
                monthly_totals.get(month) + precipitation.get(day));
            ++day;
        }
    }

    for (size_t month = 0; month < 12; ++month)
    {
        if (month != 0)
            cout << ' ';
        cout << monthly_totals.get(month);
    }
    cout << '\n';
    return 0;
}
