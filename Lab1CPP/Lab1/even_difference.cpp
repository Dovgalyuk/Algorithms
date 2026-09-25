#include <fstream>
#include <iostream>
#include <limits>

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

    if (!(input >> n))
    {
        return 1;
    }

    Array<long long> values(n);

    for (size_t i = 0; i < n; i++)
    {
        long long value;

        if (!(input >> value))
        {
            return 1;
        }

        values.set(i, value);
    }

    long long minimum_difference =
        std::numeric_limits<long long>::max();

    bool pair_found = false;

    for (size_t i = 0; i < n; i++)
    {
        if (values.get(i) % 2 != 0)
        {
            continue;
        }

        for (size_t j = i + 1; j < n; j++)
        {
            if (values.get(j) % 2 != 0)
            {
                continue;
            }

            long long difference = values.get(i) - values.get(j);

            if (difference < 0)
            {
                difference = -difference;
            }

            if (difference < minimum_difference)
            {
                minimum_difference = difference;
                pair_found = true;
            }
        }
    }

    if (!pair_found)
    {
        return 1;
    }

    std::cout << minimum_difference << '\n';

    return 0;
}
