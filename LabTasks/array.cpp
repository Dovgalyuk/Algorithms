#include <iostream>
#include <ctime>
#include "array.h"

Data calculateSum(Array *arr) {
    Data sum = 0;
    size_t size = array_size(arr);

    for (size_t i = 0; i < size; i++) {
        if(i % 2 == 0) {
            // Если считать элементы
            Data val = array_get(arr, i+1);
            // Если считать индексы
            // Data val = array_get(arr, i);
            if (val >= 0) {
                sum += val;
            }
        }
    }
    return sum;
}

int main() {
    srand(time(0));
    size_t size;

    std::cout << "Enter size of array: ";
    std::cin >> size;

    Array *arr = array_create(size);


    for (size_t i = 0 ; i < array_size(arr); ++i) {
        int r_val = rand() % 101 - 50;

        array_set(arr, i, r_val);
    }

    for (std::size_t i = 0; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << std::endl;
    }

    // Вычислили сумму
    std::cout << "Sum: " << calculateSum(arr) << std::endl;

    system("pause");
    
    array_delete(arr);
}