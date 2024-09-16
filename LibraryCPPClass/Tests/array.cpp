#include <iostream>
#include "array.h"

int main()
{
    Array *arr = new Array(10);

    if (arr->size() != 10)
    {
        std::cout << "Invalid array size\n";
        return 1;
    }

    for (int i = 0 ; i < 10 ; ++i)
        arr->set(i, i * 2);


    Array copy(*arr);

    for (int i = 0 ; i < 10 ; ++i)
    {
        if (arr->get(i) != i * 2 || copy.get(i) != i * 2){
            std::cout << "Invalid array element " << i << "\n";
            return 1;
        }
        if (arr->getAddress(i) == copy.getAddress(i)) {
            std::cout << "Copy array element have same address in array " << i << std::endl;
            return 1;
        }
    }

    delete arr;
}
