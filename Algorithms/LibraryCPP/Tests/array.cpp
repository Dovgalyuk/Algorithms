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
}
