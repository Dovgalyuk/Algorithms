#include <iostream>
#include <fstream>
#include "array.h"
#include "reader.h"

size_t task2(Array *arr, size_t count) {
    if (count < 5) {
        return 0;
    }

    size_t begin = 0, start = 0, end = 5;
    double maxsumm = 0;

    for (size_t i = 0; i < 5; i++) {
        maxsumm += array_get(arr, i);
    }

    double summ = maxsumm;

    while (end < count) {
        summ = summ - array_get(arr, start) + array_get(arr, end);
        if (summ > maxsumm) {
            maxsumm = summ;
            begin = start + 1;
        }
        start++;
        end++;
    }

    return begin;
}

int main() {
    std::ifstream input("input.txt");
    Array *arr = read_file_and_create_array(input);
    input.close();

    size_t res = task2(arr, array_size(arr));

    std::ofstream output("output.txt");
    if (output.is_open()) {
        for (size_t i = 0; i < 5; i++) {
            output << array_get(arr, res) << " ";
            res++;
        }
    }
    output.close();
    array_delete(arr);

    return 0;
}