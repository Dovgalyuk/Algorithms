#include <iostream>
#include <stdexcept>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) < 1) throw std::invalid_argument("Wrong size");
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) < 1) throw std::invalid_argument("Wrong num");
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    if (!arr) throw std::invalid_argument("Array pointer is null");

    size_t size = array_size(arr);
    double  num1 = 0, num2 = 0, sum = 0;

    for(size_t i = 0; i < size; i++) {
        
    }

}

void task2(Array *arr)
{
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
}