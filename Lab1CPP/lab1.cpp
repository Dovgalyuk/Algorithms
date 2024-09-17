#include <stdio.h>
#include "array.h"
#include <stdexcept>

using namespace std;

Array *array_create_and_read(FILE *input)
{
    int n;

    if (fscanf(input, "%d", &n) < 1) 
        throw invalid_argument("Failed to read the size");

    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if(fscanf(input, "%d", &x) < 1)
            throw invalid_argument("Failed to read the number");
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    if (!arr)
        throw invalid_argument("Array pointer is null");

    size_t size = array_size(arr);
    double sum = 0, avrg = 0;

    for (size_t i = 0; i < size; i++) {
        sum += array_get(arr, i);
    }

    avrg = sum / size;

    for (size_t i = 0; i < size; i++) {
        int curr_el = array_get(arr, i);
        if (curr_el < avrg)
            printf("task1 answer - %d \n", curr_el);
    }
}

void task2(Array *arr)
{
    if (!arr)
        throw invalid_argument("Array pointer is null");

    size_t size = array_size(arr);
    size_t maxIndex = 0, minIndex = 0; 
    int sum = 0;

    // Finding the maximum and minimum number
    for (size_t i = 0; i < size; i++) {
        if (array_get(arr, i) > array_get(arr, maxIndex))
            maxIndex = i;
        else if (array_get(arr, i) < array_get(arr, minIndex))
            minIndex = i;
    }

    // Swap using addition-substraction method
    if (maxIndex < minIndex) {
        maxIndex = maxIndex + minIndex;
        minIndex = maxIndex - minIndex;
        maxIndex = maxIndex - minIndex;
    }

    // Calculating the amount
    for (size_t i = minIndex + 1; i < maxIndex; i++) {
        sum += array_get(arr, i);
    }

    printf("task2 answer - %d \n", sum);
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE* input = fopen( argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
}
