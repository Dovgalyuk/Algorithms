#include <fstream>
#include <iomanip>
#include <iostream>

#include "../../LibraryCPPTemplate/array.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        return 1;
    }

    size_t n;

    if (!(input >> n) || n == 0)
    {
        return 1;
    }

    Array<double> resistances(n);

    for (size_t i = 0; i < n; i++)
    {
        double resistance;

        if (!(input >> resistance) || resistance <= 0)
        {
            return 1;
        }

        resistances.set(i, resistance);
    }

    double inverse_sum = 0.0;

    for (size_t i = 0; i < n; i++)
    {
        inverse_sum += 1.0 / resistances.get(i);
    }

    double total_resistance = 1.0 / inverse_sum;

    std::cout << std::fixed << std::setprecision(6)
              << total_resistance << '\n';

    return 0;
}
