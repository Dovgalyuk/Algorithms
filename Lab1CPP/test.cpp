#include <iostream>
#include "array.h"

using namespace std;
int main()
{
    Array* arr = array_create(5);

    if (array_size(arr) != 5)
    {
        array_delete(arr);
        return 1;
    }

    for (size_t i = 0; i < 5; ++i)
        array_set(arr, i, static_cast<Data>(i + 1));

    for (size_t i = 0; i < 5; ++i)
    {
        if (array_get(arr, i) != static_cast<Data>(i + 1))
        {
            array_delete(arr);
            return 1;
        }
    }

    cout << "1 2 3 4 5" << endl;

    array_delete(arr);
    return 0;
}