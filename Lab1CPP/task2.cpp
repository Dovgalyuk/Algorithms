#include <iostream>
#include <fstream>
#include "array.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: Lab1CPP_Task2 input.txt\n";
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

    int a = 0;
    int b = 0;
    input >> a >> b;

    if (a > b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    int j = 0;
    for (int i = 0; i < n; ++i)
    {
        int x = array_get(arr, i);

        if (x < a || x > b)
        {
            array_set(arr, j, x);
            ++j;
        }
    }

    for (int i = j; i < n; ++i)
        array_set(arr, i, 0);

    for (int i = 0; i < n; ++i)
        std::cout << array_get(arr, i) << " ";
    std::cout << "\n";

    array_delete(arr);
    input.close();

    return 0;
}
