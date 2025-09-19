#include <iostream>
#include "array.h"

int main()
{
    Array *arr = array_create(10, nullptr);

    if (array_size(arr) != 10)
    {
        std::cout << "Invalid array size\n";
        array_delete(arr);
        return 1;
    }

    for (int i = 0 ; i < 10 ; ++i)
    {
        array_set(arr, i, (Data)(i * 2));
    }

    array_set(arr, 0, (Data)0);

    for (int i = 0 ; i < 10 ; ++i)
    {
        if (array_get(arr, i) != (Data)(i * 2))
        {
            std::cout << "Invalid array element " << i << "\n";
            array_delete(arr);
            return 1;
        }
    }

    array_delete(arr);
}
