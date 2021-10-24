#include <iostream>
#include "cstddef"
#include "array.h"

typedef Array<int> MyArray;

int main()
{
    MyArray *arr = new MyArray(10);

    if (arr->size() != 10)
    {
        std::cout << "Invalid array size\n";
        return 1;
    }

    for (int i = 0 ; i < 10 ; ++i)
        arr->set(i, i * 2);

    for (int i = 0 ; i < 10 ; ++i)
    {
        if (arr->get(i) != i * 2)
        {
            std::cout << "Invalid array element " << i << "\n";
            return 1;
        }
    }

    delete arr;
}
