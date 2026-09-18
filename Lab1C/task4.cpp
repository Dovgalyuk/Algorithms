#include <iostream>
#include <fstream>
#include "array.h"

Array *array_create_and_read(std::ifstream& input)
{
    int n = 0;
    if (!(input >> n) or n <= 0) {
        std::cerr << "Error\n";
        return nullptr;
    }
    Array *arr = array_create(n);
    for (int i = 0 ; i < n ; ++i) {
        int x = 0;
        if (!(input >> x)) {
            std::cerr << "Error\n";
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, x);
    }
    return arr;
}

void task4_average(Array *arr) {
    size_t n = array_size(arr);
    if (n == 0) {
        return;
    }
    long long summ = 0;
    for (size_t i = 0 ; i < n ; ++i) {
        int x = array_get(arr, i);
        summ += x;
    }
    double average = (double)summ / n;
    int k = 0;
    for (size_t i = 0 ; i < n ; ++i) {
        if (array_get(arr, i) < average) {
            k++;
            std::cout << array_get(arr, i) << " ";
        }
    }
    if (k == 0) std::cout << "No" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2 or argc > 3) {
        std::cerr << "Error\n";
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error\n";
        return 1;
    }
    Array* arr = array_create_and_read(input);
    task4_average(arr);
    array_delete(arr);
    input.close();
}