#include "apfel.h"
#include <iostream>

int main() {
    Array* arr = read_array(std::cin);

    if (!arr) {
        return 1;
    }

    try {
        process_task1(arr);
        array_delete(arr);
        return 0;
    }
    catch (...) {
        array_delete(arr);
        return 1;
    }
}