#include <iostream>
#include "array.h"

int main()
{
    Array *arr = array_create(10);

    if (array_size(arr) != 10)
    {
        std::cout << "Invalid array size\n";
        array_delete(arr);
        return 1;
    }

    for (int i = 0 ; i < 10 ; ++i)
        array_set(arr, i, i * 2);

    for (int i = 0 ; i < 10 ; ++i)
    {
        if (array_get(arr, i) != i * 2)
        {
            std::cout << "Invalid array element " << i << "\n";
            array_delete(arr);
            return 1;
        }
    }

    array_delete(arr);

    Array *arr2 = array_create(0);
    if (array_size(arr2) != 0) {
        std::cout << "Invalid array size\n";
        array_delete(arr2);
        return 1;
    }
    if (array_get(arr2, 0) != Data(0))
    {
        std::cout << "Invalid array get\n";
        array_delete(arr2);
        return 1;
    }
    array_delete(arr2);

    Array *arr3 = array_create(5);
    if (array_get(arr3, 100) != Data(0)) {
        std::cout << "Invalid array get"<< "\n";
        array_delete(arr3);
        return 1;
    }

    array_set(arr3, 0, 7);
    array_set(arr3, 5, 70);
    if (array_get(arr3, 0) != 7)
    {
        std::cout << "Invalid array set\n";
        array_delete(arr3);
        return 1;
    }
    array_delete(arr3);

    if (array_size(nullptr) != 0)
    {
        std::cout << "Invalid size for nullptr\n";
        return 1;
    }

    std::cout << "All tests passed";
}
