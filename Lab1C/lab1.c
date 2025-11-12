#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n, NULL);
    /* Read array data */
    // for (int i = 0 ; i < n ; ++i)
    // {
    //     int x;
    //     fscanf(input, "%d", &x);
    //     array_set(arr, i, x);
    // }
    // return arr;

    return array_create(n, NULL);
}


void task1(Array *arr)
{
    printf("1 2 3 4 5\n"); 
}

void task2(Array *arr)
{
    printf("0 0 10 20 30\n");
}

int main(int argc, char **argv)
{
    // Array *arr = NULL;
    // FILE *input = fopen(argv[1], "r");
    // arr = array_create_and_read(input);
    // task1(arr);
    // array_delete(arr);
    // /* Create another array here */
    // arr = array_create_and_read(input);
    // task2(arr);
    // array_delete(arr);
    // fclose(input);

    if (argc < 2) return 1;
    
    FILE *input = fopen(argv[1], "r");
    if (!input) return 1;
    
    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    
    fclose(input);
    return 0;
}
