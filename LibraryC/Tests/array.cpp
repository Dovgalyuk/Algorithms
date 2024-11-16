#include <iostream>
#include "array.h"

int main()
{
    Array *arr = array_create(10, [](void *p) { delete (int*)p; });

    if (array_size(arr) != 10)
    {
        std::cout << "Invalid arrayC size\n";
        array_delete(arr);
        return 1;
    }

    for (int i = 0 ; i < 10 ; ++i)
    {
        int *d = new int;
        *d = i * 2;
        array_set(arr, i, (Data)d);
    }

    for (int i = 0 ; i < 10 ; ++i)
    {
        if (*(int*)array_get(arr, i) != i * 2)
        {
            std::cout << "Invalid arrayC element " << i << "\n";
            array_delete(arr);
            return 1;
        }
    }

    array_delete(arr);
}