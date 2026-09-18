#include <cstdio>
#include <iostream>
#include <fstream>
#include "C:\Users\timof\Algorithms\LibraryCPP\array.h"
#include "C:\Users\timof\Algorithms\LibraryCPP\array.cpp"

Array *array_create_and_read(std::ifstream& input)
{
    int n = 0;
    input >> n;
    Array* arr = array_create(n);
    for (int i = 0; i < n; ++i) {
        int x = 0;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    int changes = 0;
    int prev_sign = 0;

    size_t n = array_size(arr);
    for (size_t i = 0; i < n; i++) {
        int v = array_get(arr, i);
        if (v == 0) continue;

        int sign = (v > 0) ? 1 : -1;
        if (prev_sign != 0 && sign != prev_sign) {
            changes++;
        }
        prev_sign = sign;
    }

    std::cout << changes << "\n";
}

int main(int argc, char **argv)
{
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        return 1;
    }

    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    input.close();
    return 0;
}