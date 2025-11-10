#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    if(fscanf(input, "%d", &n) != 1)
    {
        printf("Не удалось прочитать число\n");
        return NULL;
        
    }
    else
    {
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
    
    /* Create array */
   
}

void task1(Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++) {
            printf("%d ", (int)array_get(arr, i));
        }
        printf("\n");
    }

void task2(Array *arr)
{
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    if(!input)
    {
        printf("Случилась ошибка при открытии файла");
        return 1;
    }
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
}
