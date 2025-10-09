#include <stdio.h>
#include <stdlib.h>
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
    double res = 0.0;
    for (int i = 0; i < array_size(arr); i++)
    {
        res += array_get(arr, i);
    }
    double o = (double)res / array_size(arr);
    printf("Среднее значение осадков: %.2f\n", o);
}

void task2(Array *arr)
{
    int* res = (int*)malloc(array_size(arr) * sizeof(int));;
    int o = 0;
    for (int i = 0; i < array_size(arr); i++)
    {
        o = 0;
        for (int g = 0; g < array_size(arr); g++)
        {
            if ((array_get(arr, i) == array_get(arr, g)) && (i != g)) {
                o++;
            }
        }
        if (o == 0) {
            res[i] = 1;
        }
        else {
            res[i] = 0;
        }
    }
    printf("Уникальные элементы: ");
    for (int i = 0; i < array_size(arr); i++) {
        if (res[i] == 1) {
            printf("%d ", array_get(arr, i));
        }
    }
    printf("\n");
    free(res);
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
