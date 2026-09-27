#include "array.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

int main()
{
    Array* arr = array_create(5);
    assert(array_size(arr) == 5);

    for (size_t i = 0; i < array_size(arr); i++)
    {
        array_set(arr, i, static_cast<Data>(i * 2));
    }

    for (size_t i = 0; i < array_size(arr); i++)
    {
        assert(array_get(arr, i) == static_cast<Data>(i * 2));
    }

    bool caughtOnGet = false;
    try
    {
        array_get(arr, array_size(arr));
    }
    catch (const std::out_of_range&)
    {
        caughtOnGet = true;
    }
    assert(caughtOnGet);

    bool caughtOnSet = false;
    try
    {
        array_set(arr, array_size(arr) + 10, 1);
    }
    catch (const std::out_of_range&)
    {
        caughtOnSet = true;
    }
    assert(caughtOnSet);

    array_destroy(arr);

    Array* empty = array_create(0);
    assert(array_size(empty) == 0);
    array_destroy(empty);

    std::cout << "Все проверки массива пройдены успешно" << std::endl;
    return 0;
}
