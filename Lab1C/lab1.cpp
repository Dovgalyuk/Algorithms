#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array.h"

Array* array_create_and_read(FILE* input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1)
        return NULL;

    Array* arr = array_create(n, NULL); 
    for (int i = 0; i < n; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}


void task1(Array* arr)
{
    size_t n = array_size(arr);
    if (n == 0) return;

    double sum = 0;
    for (size_t i = 0; i < n; ++i)
        sum += array_get(arr, i);

    double avg = sum / n;

    int closest = (int)array_get(arr, 0);
    double min_diff = fabs(closest - avg);

    for (size_t i = 1; i < n; ++i)
    {
        int val = (int)array_get(arr, i);
        double diff = fabs(val - avg);
        if (diff < min_diff)
        {
            min_diff = diff;
            closest = val;
        }
    }

    printf("Task1: element closest to average (%.2f) is %d\n", avg, closest);
}


void task2(Array* arr, FILE* input)
{
    size_t n = array_size(arr);
    if (n == 0) return;

    int direction, steps;
    fscanf(input, "%d %d", &direction, &steps); 

    if (steps > (int)n) steps = (int)n; 

    Array* res = array_create(n, NULL);

    for (size_t i = 0; i < n; ++i)
        array_set(res, i, 0);

    if (direction == 0)
    {
        for (size_t i = 0; i + steps < n; ++i)
            array_set(res, i, array_get(arr, i + steps));
    }
    else 
    {
        for (size_t i = steps; i < (int)n; ++i)
            array_set(res, i, array_get(arr, i - steps));
    }

    printf("Task2: shifted array = ");
    for (size_t i = 0; i < n; ++i)
        printf("%d ", (int)array_get(res, i));
    printf("\n");

    array_delete(res);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input)
    {
        perror("File open error");
        return 1;
    }

    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr, input);
    array_delete(arr);

    fclose(input);
    return 0;
}
