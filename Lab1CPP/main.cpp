#include "lab1.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    arr = task1(arr, input);
    for(size_t i = 0; i < array_size(arr); i++)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    arr = task2(arr);
    std::cout << array_size(arr) << std::endl;
    for(size_t i = 0; i < array_size(arr); i++)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;
    array_delete(arr);
    fclose(input);
    return 0;
}