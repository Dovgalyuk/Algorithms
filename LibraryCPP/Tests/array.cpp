#include <iostream>
#include "array.h"

int main()
{
    size_t size = 10;
    int* arr = array_create(size);

    if (array_size(arr, size) != size)
    {
        std::cout << "Invalid array size\n";
        array_delete(arr);
        return 1;
    }

    for (size_t i = 0; i < size; ++i)
        array_set(arr, i, i * 2);

    for (size_t i = 0; i < size; ++i)
    {
        if (array_get(arr, i) != static_cast<int>(i) * 2)

        {
            std::cout << "Invalid array element " << i << "\n";
            array_delete(arr);
            return 1;
        }
    }

    array_delete(arr);
    std::cout << "Test passed successfully!\n";
    return 0;
}
