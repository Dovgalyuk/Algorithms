#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "array.h"

void qsort(Array *arr, size_t start, size_t end){
    if (start >= end) return;

    size_t left = start;
    size_t right = end;
    Data pivot = array_get(arr, start + (end - start) / 2); 

    while (left <= right){
        while (array_get(arr, left) < pivot) left++;
        while (array_get(arr, right) > pivot) right--;

        if (left <= right){
            Data temp = array_get(arr, right);
            array_set(arr, right, array_get(arr, left));
            array_set(arr, left, temp);
            left++; right--;
            if (right > end) right++;

        }
    }

    qsort(arr, start, right);
    qsort(arr, left, end);
}

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(void)
{
    size_t n;
    Array *arr = NULL;
    scanf("%lu", &n);
    arr = array_create(n);
    for (size_t index{0}; index < n; ++index) array_set(arr, index, rand() % 100);

    for (size_t index{0}; index < array_size(arr); ++index){
        if (array_get(arr, index) % 2 == 0) 
            array_set(arr, index, array_get(arr, index) * array_get(arr, index));
        else array_set(arr, index, 2 * array_get(arr, index));
    }

    array_delete(arr);
}

void task2(void)
{
    size_t size_arr;
    Array *arr = NULL;
    scanf("%lu", &size_arr);
    arr = array_create(size_arr);
    for (size_t index{0}; index < size_arr; ++index) array_set(arr, index, rand() % 100);
    qsort(arr, 0, size_arr - 1);

    for (size_t index{1}; index < size_arr; ++index){
        if (index == (size_arr - 1)){
            if (index == 1){
                if (array_get(arr, 0) == array_get(arr, 1)) printf("%d ", array_get(arr, 0));
                continue;
            }
            if ((array_get(arr, index - 1) == array_get(arr, index)) && (array_get(arr, index - 2) != array_get(arr, index)))
                printf("%d ", array_get(arr, index));
            continue;
        };

        if (array_get(arr, index) != array_get(arr, index + 1)){
            if (index == 1) {
                if (array_get(arr, 0) == array_get(arr, 1))
                    printf("%d ", array_get(arr, 1));
                continue;
            }

            if ((array_get(arr, index - 1) == array_get(arr, index)) && (array_get(arr, index - 2) != array_get(arr, index)))
                printf("%d ", array_get(arr, index));
        }
    }

    array_delete(arr);
    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc > 1){
        Array *arr = NULL;
        FILE *input = fopen(argv[1], "r");
        arr = array_create_and_read(input);
        array_delete(arr);
        /* Create another array here */
        arr = array_create_and_read(input);
        array_delete(arr);
        fclose(input);
    }

    task1();
    task2();

    return 0;
}
