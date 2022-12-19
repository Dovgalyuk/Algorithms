#include <iostream>
#include <ctime>
#include "array.h"

Data getTheMostPopularNubmerInArray(Array* arr){

    size_t size = array_size(arr);
    int k, l, max;
    max = array_get(arr,0);

    for (int i = 0; i < size - 1; i++) {
        k = 1;
        for (int j = i + 1; j < size; j++) {
            if (array_get(arr, i) == array_get(arr, j)) k++;
            if (k > max) { max = k; l = i; }
        }
    }
    for (int i = 0; i < size - 1; i++) {
        k = 1;
        for (int j = i + 1; j < size; j++)
        {
            if (array_get(arr, i) == array_get(arr, j)) k++;
        }
        if (k == max) std::cout << array_get(arr, i) << " ";
    }
    return max;
}

main() {
    srand(time(0));
    size_t size;

    std::cout << "Enter size of array: ";
    std::cin >> size;

    Array* arr = array_create(size);


    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = rand() % 31;
        array_set(arr, i, value);
    }

    for (std::size_t i = 0; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << std::endl;
    }

    int number = getTheMostPopularNubmerInArray(arr);

    std::cout << "number - " << number << std::endl;

    system("pause");

    array_delete(arr);
}