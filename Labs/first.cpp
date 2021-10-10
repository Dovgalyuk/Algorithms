#include <iostream>
#include "array.h"

int main()
{
    srand(time(NULL));
    int  sum = 0;
    size_t  size;

    std::cout << "Enter the size of the array = ";
    std::cin >> size;

    Array* array = array_create(size);

    for (size_t i = 0; i < size; i++)
    {
        array_set(array, i, rand() % 999);
        if (array_get(array, i) < 20)
            sum += array_get(array, i);
    }

    std::cout << "sum of elements is less than 20 = " << sum;

    array_delete(array);
    return 0;
}