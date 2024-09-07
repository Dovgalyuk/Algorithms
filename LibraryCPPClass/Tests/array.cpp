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
        arr->set(20, 5);  // error index
        std::cout << "set() set() does not handle invalid index\n";
        return 1;
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Caught expected out_of_range exception for set() with invalid index\n";
    }

    try
    {
        arr->get(20);  // error index
        std::cout << "set() set() does not handle invalid index\n";
        return 1;
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Caught expected out_of_range exception for get() with invalid index\n";
    }

    delete arr;
}
