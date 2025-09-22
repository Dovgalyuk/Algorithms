#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    if(fscanf(input, "%d", &n) != 1) return NULL; 
    /* Create array */
    Array *arr = array_create((size_t)n, NULL);
    if(!arr) return NULL;
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, (Data)x);
    }
    return arr;
}

void task1(Array *arr)
{
    size_t size = array_size(arr);
    for(size_t i = 0; i < size / 2; i++){
        Data t1 = array_get(arr, i);
        Data t2 = array_get(arr, size - i - 1);
        array_set(arr, i, t2);
        array_set(arr, size - i - 1, t1);
    }
    for(size_t i = 0; i < size; i++){
        printf("%d ", (int)array_get(arr, i));
    }
    printf("\n");
}

void task2(Array *arr)
{
    if(array_size(arr) < 5){
        return;
    }
    int s1 = 0;
    size_t i1 = 0;
    for(size_t i = 0; i < 5; i++){
        s1 += (int)array_get(arr,i);
    }
    int s2 = s1;
    for(size_t i = 1; i <= array_size(arr) - 5; i++){
        s2 = s2 - (int)array_get(arr, i - 1) + (int)array_get(arr,i + 4);
        if(s2 > s1){
            s1 = s2;
            i1 = i;
        }
    }

    for(size_t i = 0; i < 5; i++){
        printf("%d ", (int)array_get(arr, i1 + i));
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    Array *arr1 = array_create_and_read(input);
    task2(arr1);
    array_delete(arr1);
    fclose(input);
}
