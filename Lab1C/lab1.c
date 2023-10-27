#include <stdio.h>
#include <stdlib.h>
#include "../LibraryC/array.c"

void task1(Array *arr)
{
    long sum = 0;
    long long mul = 1;

    printf("array: ");

    for (size_t i = 0; i < array_size(arr); i++)
    {
        printf("%d; ", *(int *)array_get(arr, i));
        sum += *(int *)array_get(arr, i);
        mul *= *(int *)array_get(arr, i);
    }

    printf("sum: %ld, mul: %lld\n", sum, mul);
}

void task2(Array *arr)
{
    printf("array: ");

    for (size_t i = 0; i < array_size(arr); i++)
    {
        printf("%d; ", *(int *)array_get(arr, i));
    }

    printf("undividable elements: ");

    for (size_t j = 0, i = 0; i < array_size(arr);)
    {
        if (i != j && *(int *)array_get(arr, i) % *(int *)array_get(arr, j) == 0)
        {
            j = 0;
            i++;
        }
        if (j == array_size(arr) - 1)
        {
            printf("%d; ", *(int *)array_get(arr, i));
            j = 0;
            i++;
        }
        else
            j++;
    }
    printf("\n");
}

int main()
{
    Array *arr = NULL;
    /* Create array here */
    size_t size;
    scanf("%zu", &size);
    arr = array_create(size, free);
    for (size_t i = 0; i < array_size(arr); i++)
    {
        int *ptr = (int *)malloc(sizeof(int));
        *ptr = rand();
        array_set(arr, i, (void *)ptr);
    }
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    scanf("%zu", &size);
    arr = array_create(size, free);
    for (size_t i = 0; i < array_size(arr); i++)
    {
        int *ptr = (int *)malloc(sizeof(int));
        *ptr = rand();
        array_set(arr, i, (void *)ptr);
    }
    task2(arr);
    array_delete(arr);
}
