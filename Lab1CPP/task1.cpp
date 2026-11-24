#include <fstream>
#include <iostream>
#include "array.h"

void fill_digits(Array *arr)
{
    int remainder = 1;
    for (size_t i = 0 ; i < array_size(arr) ; ++i)
    {
        remainder *= 10;
        array_set(arr, i, remainder / 17);
        remainder %= 17;
    }
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
    fill_digits(arr);

    std::ofstream output(argv[2]);
    for (size_t i = 0 ; i < array_size(arr) ; ++i)
        output << array_get(arr, i) << ' ';
    output << '\n';

    array_delete(arr);
}
