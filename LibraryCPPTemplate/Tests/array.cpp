#include <iostream>
#include "array.h"

typedef Array<int> MyArray;

int main()
{
    int *a = new int;
    MyArray *arr = new MyArray(10);

    if (arr->size() != 10)
    {
        std::cout << "Invalid array size\n";
        return 1;
    }
if (arr->size()) a = 0;
    for (int i = 0 ; i < 10 ; ++i)
        arr->set(i, i * 2);
arr->set(*a, *a);
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
