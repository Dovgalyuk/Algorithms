#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <climits>
#include "array.h"

Array* array_create_and_read(std::ifstream& input)
{
    int n = 0;
    if (input >> n) {
        Array* arr = array_create(n);
        for (int i = 0; i < n; ++i) {
            int x = 0;
            if (input >> x) {
                array_set(arr, i, x);
            }
        }
        return arr;
    }
    return nullptr;
}

void task2(Array* arr)
{
    if (!arr) return;
    size_t n = array_size(arr);

    int min_diff = INT_MAX;
    bool found = false;

    for (size_t i = 0; i < n; ++i) {
        int val1 = array_get(arr, i);
        if (val1 % 2 != 0) continue;
        for (size_t j = i + 1; j < n; ++j) {
            int val2 = array_get(arr, j);
            if (val2 % 2 != 0) continue;
            if (val1 != val2) {
                int diff = std::abs(val1 - val2);
                if (diff < min_diff) {
                    min_diff = diff;
                    found = true;
                }
            }
        }
    }

    if (found) std::cout << min_diff << "\n";
    else std::cout << -1 << "\n";
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        return 1;
    }
    Array* arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    input.close();
    return 0;
}