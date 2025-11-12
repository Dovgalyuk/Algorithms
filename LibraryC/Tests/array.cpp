#include <iostream>
#include "array.h"

using namespace std;

int main()
{
    Array *arr = array_create(5, nullptr);

    if (array_size(arr) != 5)
    {
        std::cout << "Invalid array size\n";
        array_delete(arr);
        return 1;
    }

    for (int i = 0; i < 5; ++i) {
        array_set(arr, i, i + 1); 
        cout << array_get(arr, i) << " ";  
    }
    cout << endl;

    cout << "Size: " << array_size(arr) << endl;

    array_delete(arr);

    return 0;
    // Array *arr = array_create(10, [](void *p) { delete (int*)p; });

    // if (array_size(arr) != 10)
    // {
    //     std::cout << "Invalid array size\n";
    //     array_delete(arr);
    //     return 1;
    // }

    // for (int i = 0 ; i < 10 ; ++i)
    // {
    //     int *d = new int;
    //     *d = i * 2;
    //     array_set(arr, i, (Data)d);
    // }

    // array_set(arr, 0, (Data)new int(0));

    // for (int i = 0 ; i < 10 ; ++i)
    // {
    //     if (*(int*)array_get(arr, i) != i * 2)
    //     {
    //         std::cout << "Invalid array element " << i << "\n";
    //         array_delete(arr);
    //         return 1;
    //     }
    // }

    // array_delete(arr);
}
