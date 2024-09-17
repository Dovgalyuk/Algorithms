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
    for (size_t i = 0 ; i < (size_t)n ; ++i)
    {
        int* x = malloc(sizeof(int));
        fscanf(input, "%d", x);
        array_set(arr, i, (Data)x);
    }
    return arr;
}

void task1(Array *arr)
{
    int sum_of_1h = 0;
    int sum_of_2h = 0;
    size_t size = array_size(arr);
    for (size_t i = 0; i < (size_t) (size/2); i++)
    {
        sum_of_1h += *(int*)array_get(arr, i);
    }
    for (size_t i = (size_t) (size/2); i < size; i++)
    {
        sum_of_2h += *(int*)array_get(arr, i);
    }
    if (sum_of_1h > sum_of_2h)
    {
        printf("More precipitation fell in the first half of the month\n");
    }
    else if (sum_of_1h < sum_of_2h)
    {
        printf("More precipitation fell in the second half of the month\n");
    }
    else
    {
        printf("equal amounts of precipitation fell in both halves of the month\n");
    }

    int first_decade = 0;
    int second_decade = 0;
    int third_decade = 0;
    for (size_t i = 0; i < 10; i++)
    {
        first_decade += *(int*)array_get(arr, i);
    }
    for (size_t i = 10; i < 20; i++)
    {
        second_decade += *(int*)array_get(arr, i);
    }
    for (size_t i = 20; i < size; i++)
    {
        third_decade += *(int*)array_get(arr, i);
    }
    if ((first_decade > second_decade) && (first_decade > third_decade))
    {
        printf("More precipitation fell in the first decade of the month\n");
    }
    else if (second_decade > third_decade)
    {
        printf("More precipitation fell in the second decade of the month\n");
    }
    else
    {
        printf("More precipitation fell in the third decade of the month\n");
    }
    
    
}

void task2(Array *arr, FILE *input)
{
    int a, b;
    fscanf(input, "%d %d", &a, &b);
    size_t end_of_arr = array_size(arr);
    for (size_t i = 0; i < end_of_arr; i++)
    {
        if (*(int*)array_get(arr, i) >= a && *(int*)array_get(arr, i) <= b)
        {
            int* zero = malloc(sizeof(int));
            *zero = 0;
            array_set(arr, i, (array_get(arr, end_of_arr - 1)));
            array_set(arr, end_of_arr-1, (Data)zero);
            end_of_arr--;
        }
    }
    for (size_t i = 0; i < array_size(arr); i++)
    {
        printf("%d ", *(int*)array_get(arr, i));
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    printf("%s \n", argv[1]);
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr, input);
    array_delete(arr);
    fclose(input);
}
