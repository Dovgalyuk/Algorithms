#include <stdio.h>
#include "array.h"

void task1(Array *arr)
{
}

void task2(Array *arr)
{
}

int main()
{
    Array *arr = NULL;
    /* Create array here */
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    task2(arr);
    array_delete(arr);
}