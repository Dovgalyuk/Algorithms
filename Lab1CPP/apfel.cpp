#include "apfel.h"
#include <iostream>
#include <stdexcept>

Array* read_array(std::istream& stream) {
    size_t size;
    if (!(stream >> size) || size == 0) {
        return nullptr;
    }

    Array* arr = array_create(size);
    for (size_t i = 0; i < size; ++i) {
        Data val;
        if (!(stream >> val)) {
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, val);
    }
    return arr;
}

static unsigned long long factorial(Data n) {
    if (n < 0) {
        throw std::invalid_argument("Negative value for factorial");
    }
    if (n > 20) {
        throw std::out_of_range("Factorial value causes integer overflow");
    }
    unsigned long long res = 1;
    for (Data i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

void process_task1(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; ++i) {
        Data val = array_get(arr, i);
        unsigned long long fact = factorial(val);
        std::cout << fact << (i + 1 == size ? "" : " ");
    }
    std::cout << std::endl;
}

void process_task2(Array* arr) {
    size_t size = array_size(arr);
    bool first = true;
    for (size_t i = 0; i < size; ++i) {
        Data elem = array_get(arr, i);
        if (elem <= 0) {
            throw std::invalid_argument("Non-positive element found");
        }
        bool divisible = false;
        for (size_t j = 0; j < size; ++j) {
            if (i != j) {
                Data other = array_get(arr, j);
                if (other > 0 && elem % other == 0) {
                    divisible = true;
                    break;
                }
            }
        }
        if (!divisible) {
            if (!first) std::cout << " ";
            std::cout << elem;
            first = false;
        }
    }
    std::cout << std::endl;
}