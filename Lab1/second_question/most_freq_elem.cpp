#include <iostream>
#include <fstream>
#include "array.h"

Data find_most_frequent(const Array* arr){
    
    int frequency[1001] = {};

    for(size_t i = 0; i < array_size(arr); ++i){
        Data value = array_get(arr, i);

        ++frequency[value];
    }

    Data mostFrequent = 0;

    for(Data value = 1; value <= 1000; ++value){
        if(frequency[value] > frequency[mostFrequent]){
            mostFrequent = value;
        }
    }

    return mostFrequent;
}


int main(int argc, char* argv[])
{

    std::ifstream input(argv[1]);

    if (!input){
       return 1;
    }
 

    size_t n;
    input >> n;

    if (n <= 0){
        return 1;
    }
 
    Array* arr = array_create(n);

    for (size_t i = 0; i < n; ++i)
    {
        int value;
        input >> value;
        array_set(arr, i, value);
    }

    Data result = find_most_frequent(arr);

    std::cout << result;

    array_delete(arr);

    return 0;
}