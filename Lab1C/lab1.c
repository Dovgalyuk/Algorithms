#include <stdio.h>
#include "array.h"
#include <stdlib.h>

void task1(Array *arr)
{
}

void task2(Array *arr)
{
}

int main()
{
    task1(arr);

    // Delete the first array
    array_delete(arr);

    // Create another array
    arr = array_create(); // Create a new 'Array' instance

    task2(arr);

    // Delete the second array
    array_delete(arr);

    return 0;
}
