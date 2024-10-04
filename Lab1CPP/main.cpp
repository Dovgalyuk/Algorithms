#include "lab1.h"
#include <iostream>

int main(int argc, char **argv)
{
    FILE *input = fopen(argv[1], "r");

    Array *arr = array_create_and_read(input);


    int sum = task1(arr, input);  

    array_delete(arr);

    arr = array_create_and_read(input);
    
    size_t result_size;
    Array* result = task2(arr, result_size);

    for (size_t i = 0; i < result_size; ++i) {
        std::cout << array_get(result, i) << " ";
    }
    std::cout << std::endl;

    array_delete(arr);
    array_delete(result);

    fclose(input);
    return 0;
}
