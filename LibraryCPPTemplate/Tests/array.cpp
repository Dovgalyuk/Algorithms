#include <iostream>
#include "../array.h"

typedef Array<int> MyArray;

int _main()
{
    MyArray *arr = new MyArray(10);

    if (arr->size() != 10)
    {
        std::cout << "Invalid array size\n";
        return 1;
    }

    for (int i = 0; i < 10; ++i)
        arr->set(i, i * 2);

    MyArray copy(*arr);

    for (int i = 0; i < 10; ++i)
    {
        if (arr->get(i) != i * 2 || copy.get(i) != i * 2)
        {
            std::cout << "Invalid array element " << i << "\n";
            return 1;
        }
    }

    delete arr;
    return 0;
}

int main()
{
    MyArray k(15);
    std::cout << k.get(5);
    k.set(5, 3);
    std::cout << k.get(5);
    MyArray b(16);
    k = b;
    std::cout << k.get(5);
    std::cout << std::endl;
}
