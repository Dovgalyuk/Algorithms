#include <stdio.h>
#include "array.h"

Array* array_create_and_read(FILE* input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr) {
    int maxElement = 0;
    int firstMaxElement = 0;
    int lastMaxElement = 0;

    for (int i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) > maxElement) {
            maxElement = array_get(arr, i);
            firstMaxElement = i;
            lastMaxElement = i;
        }
        else if (array_get(arr, i) == maxElement) {
            lastMaxElement = i;
        }
    }


    printf("%d %d\n", firstMaxElement, lastMaxElement);
}

void task2(Array* arr) {
    int maxSum = 0;
    for (int i = 0; i < array_size(arr) - 5; i++) {
        if (array_get(arr, i) + array_get(arr, i + 1) + array_get(arr, i + 2) + array_get(arr, i + 3) + array_get(arr, i + 4) > maxSum) {
            maxSum = array_get(arr, i) + array_get(arr, i + 1) + array_get(arr, i + 2) + array_get(arr, i + 3) + array_get(arr, i + 4);
        }
    }
    printf("%d\n", maxSum);

}

int main(int argc, char** argv)
{
    Array* arr = NULL;
    FILE* input = fopen_s(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
}
