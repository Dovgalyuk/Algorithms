#include <iostream>
#include <fstream>
#include "array.h"

void find_two_smallest(const Array* arr, Data& min1, Data& min2){
    min1 = array_get(arr, 0);
    min2 = array_get(arr, 1);

    if (min2 < min1)
    {
        int temp = min1;
        min1 = min2;
        min2 = temp;
    }

    for (size_t i = 2; i < array_size(arr); ++i)
    {
        Data value = array_get(arr, i);

        if (value < min1)
        {
            min2 = min1;
            min1 = value;
        }
        else if (value < min2)
        {
            min2 = value;
        }
    }
}

int main(int argc, char* argv[])
{

    std::ifstream input(argv[1]);

    if (!input){
       return 1;
    }
 

    size_t n;
    input >> n;

    if (n < 2){
        return 1;
    }
 
    Array* arr = array_create(n);

    for (size_t i = 0; i < n; ++i)
    {
        int value;
        input >> value;
        array_set(arr, i, value);
    }

    Data min1;
    Data min2;

    find_two_smallest(arr, min1, min2);

    

    std::cout << min1 << " " << min2 << "\n";

    array_delete(arr);

    return 0;
}