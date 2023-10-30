#include <stdio.h>
#include <stdlib.h>
#include "../LibraryCPPTemplate/array.h"

void task1(Array<int> *arr)
{
    long sum = 0;
    long long mul = 1;

    printf("array: ");

    for (size_t i = 0; i < arr->size(); i++)
    {
        printf("%d; ", arr->get(i));
        sum += arr->get(i);
        mul *= arr->get(i);
    }

    printf("sum: %ld, mul: %lld\n", sum, mul);
}

void task2(Array<int> *arr)
{
    printf("array: ");

    for (size_t i = 0; i < arr->size(); i++)
    {
        printf("%d; ", arr->get(i));
    }

    printf("undividable elements: ");

    for (size_t j = 0, i = 0; i < arr->size();)
    {
        if (i != j && arr->get(i) % arr->get(j) == 0)
        {
            j = 0;
            i++;
        }
        if (j == arr->size() - 1)
        {
            printf("%d; ", arr->get(i));
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
    Array<int> *arr = nullptr;

    /* Create array here */

    size_t size;
    scanf("%zu", &size);
    arr = new Array<int>(size);

    for (size_t i = 0; i < arr->size(); i++)
        arr->set(i, rand() % 100);

    task1(arr);
    delete arr;

    /* Create another array here */

    scanf("%zu", &size);
    arr = new Array<int>(size);

    for (size_t i = 0; i < arr->size(); i++)
        arr->set(i, rand() % 100);

    task2(arr);
    delete arr;
}
