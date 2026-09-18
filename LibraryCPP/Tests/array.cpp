#include <iostream>
#include "array.h"
using namespace std;

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

    array_set(arr, 10, 100);

    if (array_get(arr, 10) != 0) {
        cout << "Out of bounds test failed\n";
        array_delete(arr);
        return 1;
    }

    Array* arr0 = array_create(0);

    if (array_size(arr0) != 0) {
        cout << "Test failed, empty array\n";
        array_delete(arr0);
        array_delete(arr);
        return 1;
    }
    array_delete(arr);
    array_delete(arr0);

    cout << "All array tests passed!\n";
    return 0;
}