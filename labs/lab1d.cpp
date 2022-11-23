#include <iostream>
#include "array.h"

void fillArray(Array* arr) {
    int number;
    int size = array_size(arr);
    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter number of " << i+1 << " element: ";
        std::cin >> number;
        array_set(arr, i, number);
    }
}

void printArray(Array* arr) {
    int size = array_size(arr);
    for (int i = 0; i < size; i++)
    {
        std::cout << array_get(arr, i) << " ";
    }
}

void checkNumbers(Array* arr, int min, int max) {
    int value;
    int size = array_size(arr);
    for (int i = 0; i < size; i++)
    {
        value = array_get(arr, i);
        if (value >= min && value <=max)
        {
            for (int j = i; j < size; j++)
            {
                array_set(arr, j, array_get(arr, j + 1));
            }
            array_set(arr, size, 0);
            size--;
            i--;
        }
    }
}

int main()
{
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    Array* arr = array_create(size);

    fillArray(arr);

    int a, b;
    
    std::cout << "Enter minimum: ";
    std::cin >> a;

    std::cout << "Enter maximum: ";
    std::cin >> b;

    checkNumbers(arr, a, b);
    printArray(arr);
    
    array_delete(arr);

    return(0);
}
