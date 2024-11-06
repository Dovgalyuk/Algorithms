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
        if (arr->get(i) != i * 2
            || copy.get(i) != i * 2)
        {
            std::cout << "Invalid array element " << i << "\n";
            return 1;
        }
    }

    try 
    {
        arr->set(32, 8);
        std::cout << "set() - Check for index. Doesn't handle invalid index.";
        return 1;
    }
    catch (const std::out_of_range&)
    {
        std::cout << "set() - Check for index. Expected out of range with invalid index.";
    }

    try 
    {
        arr->get(16);
        std::cout << "get() - Check for index. Doesn't handle invalid index";
        return 1;
    }
    catch (const std::out_of_range&)
    {
        std::cout << "get() - Check for index. Expected out of range with invalid index.";
    }

    delete arr;
}
