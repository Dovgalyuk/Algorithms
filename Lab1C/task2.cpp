#include <iostream>
#include <fstream>
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
    int count_arr[1001] = { 0 };
    for (size_t i = 0; i < n; i++) {
        int val = array_get(arr, i);
        if (val >= 0 && val <= 1000) {
            count_arr[val]++;
        }
    }
    int max_count = -1;
    int num = 0;
    for (int x = 0; x <= 1000; x++) {
        if (count_arr[x] > max_count) {
            max_count = count_arr[x];
            num = x;
        }
    }
    std::cout << num << "\n";
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
