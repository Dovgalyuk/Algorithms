#include <fstream>
#include <iostream>
#include "array.h"

const int MAX_VALUE = 1000;

void print_pairs(const Array *arr, std::ostream &output)
{
    Array *count = array_create(MAX_VALUE + 1);
    for (size_t i = 0 ; i < array_size(arr) ; ++i)
    {
        Data x = array_get(arr, i);
        array_set(count, x, array_get(count, x) + 1);
    }
    for (int x = 0 ; x <= MAX_VALUE ; ++x)
        if (array_get(count, x) == 2)
            output << x << ' ';
    output << '\n';
    array_delete(count);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " input output\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    size_t n;
    if (!(input >> n))
    {
        std::cerr << "Can't read array size\n";
        return 1;
    }

    Array *arr = array_create(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        Data x;
        if (!(input >> x) || x < 0 || x > MAX_VALUE)
        {
            std::cerr << "Invalid element " << i << "\n";
            array_delete(arr);
            return 1;
        }
        array_set(arr, i, x);
    }

    std::ofstream output(argv[2]);
    print_pairs(arr, output);

    array_delete(arr);
}
