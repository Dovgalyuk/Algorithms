#include <iostream>
#include <fstream>
#include "array.h"

Array* array_read(std::ifstream& input) {
    int n;
    input >> n;
    Array* arr = array_create(n);
    for (int i = 0; i < n; ++i) {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void T2(Array* arr) {
    int size = array_size(arr);
    const int MAX_VALUE = 1000;
    int freq[MAX_VALUE+1] = {0};

    for (int i = 0; i < size; ++i) {
        int val = array_get(arr, i);
        if (val >= 0 && val <= MAX_VALUE)
            freq[val]++;

    }

    int most_frequent = 0;
    int max_count = 0;
    for (int j = 0; j <= MAX_VALUE; ++j) {
        if (freq[j] > max_count) {
            max_count = freq[j];
            most_frequent = j;
        }
    }

    if (max_count <= 1) {
    std::cout << "Нет повторений" << std::endl;
    } else {
    std::cout << "Самое часто встречающееся число: " << most_frequent << std::endl;
    }
}

int main(int argc, char** argv) {
    std::ifstream input(argv[1]);
    Array* arr = array_read(input);
    T2(arr);
    array_delete(arr);
    return 0;
}