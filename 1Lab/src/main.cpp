#include "../include/array.h"
#include <cassert>
#include <iostream>

int main()
{
    array<int> arr(53);
    assert(arr.size() == 53);

    for (size_t i = 0; i < arr.size(); i++)
    {
        arr[i] = i;
    }

    assert(arr.size() != 13);
    assert(arr[34] == 34);

    arr[5] = 555;

    assert(arr[5] == 555);

    std::cout << "All array tests passed" << std::endl;
    return 0;
}