#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n, NULL);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    int min = (int)array_get(arr, 0);
    int max = (int)array_get(arr, 0);
    for (size_t i = 1; i < array_size(arr); i++) {
        int val = (int)array_get(arr, i);
        if (val < min) min = val;
        if (val > max) max = val;
    }
    double avg = (min + max) / 2.0;
        for (size_t i = 0; i < array_size(arr); i++) {
        int val = (int)array_get(arr, i);
        if (val < avg) {
            printf("%zu ", i);
        }
    }
    return;
}

void task2(Array *arr)
{
    int maxNumber = (int)array_get(arr, 0);
    int maxFrequent = 1;
    int maxFrequentIdx = 0;
    for (size_t i = 0; i < array_size(arr); i++) {
        int count = 0;
        int val = (int)array_get(arr, i);
        for (size_t j = 0; j < array_size(arr); j++) {
            if (val == (int)array_get(arr, j)) {
                count++;
            }
        }
        if (count > maxFrequent) {
            maxFrequent = count;
            maxNumber = val;
            maxFrequentIdx = (int)i;
        }

    }
    printf("%d %d %d\n", maxNumber, maxFrequent, maxFrequentIdx);
    return;
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
