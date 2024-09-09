#include <cstdio>
#include <stdexcept>
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

void qsort(Array *arr)
{
    qsort(arr, 0, array_size(arr) - 1);
}

Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) < 1) throw std::invalid_argument("Failed to read size");
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) < 1) throw std::invalid_argument("Failed to read number");
        array_set(arr, i, x);
    }

    return arr;
}

void task1(Array *arr)
{
    size_t size = array_size(arr);

    for (size_t index{0}; index < size; ++index){
        if (array_get(arr, index) % 2 == 0) 
            array_set(arr, index, array_get(arr, index) * array_get(arr, index));
        else array_set(arr, index, 2 * array_get(arr, index));
    }
}

void task2(Array *arr)
{
    if (!arr) std::invalid_argument("Array pointer is null");
    if (array_size(arr) < 2) return;
    qsort(arr);

    unsigned cnt = 1;
    size_t size_arr = array_size(arr);
    Data item = array_get(arr, 0);

    for (size_t index{1}; index < size_arr; ++index){
        if (array_get(arr, index) == item) cnt++;
        else {
            if (cnt == 2) printf("%d ", item);
            cnt = 1;
            item = array_get(arr, index);
        }
    }

    if (cnt == 2) printf("%d", item);
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
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}
