#include <iostream>
#include <fstream>
#include "array.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: Lab1CPP_Task1 input.txt\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cout << "Cannot open file " << argv[1] << "\n";
        return 1;
    }

    int n = 0;
    input >> n;

    Array *arr = array_create(n);
    for (int i = 0; i < n; ++i)
    {
        int x = 0;
        input >> x;
        array_set(arr, i, x);
    }

    int k1 = 0;
    int k2 = 0;
    input >> k1 >> k2;

    int value1 = array_get(arr, k1);
    int value2 = array_get(arr, k2);

    for (int i = 0; i < n; ++i)
    {
        int x = array_get(arr, i);

        if (x > 0)
            x = x - value1;
        else
            x = x - value2;

        array_set(arr, i, x);
    }

    for (int i = 0; i < n; ++i)
        std::cout << array_get(arr, i) << " ";
    std::cout << "\n";

    array_delete(arr);
    input.close();

    return 0;
}
