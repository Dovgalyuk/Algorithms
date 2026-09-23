#include "tasks.h"

void task1(Array *arr)
{
    if (!arr) return;

    size_t arr_size = array_size(arr);

    Array *array_of_even_numbers = NULL;
    size_t new_array_size = 0;
    for (size_t i = 0; i < arr_size; i++) {
        if (array_get(arr, i) % 2 == 0) {
            new_array_size++;
        }
    }

    array_of_even_numbers = array_create(new_array_size);
    size_t index = 0;

    for (size_t i = 0; i < arr_size; i++) {
        if (array_get(arr, i) % 2 == 0) {
            array_set(array_of_even_numbers, index++, Data(i));
        }
    }

    for (size_t i = 0; i < new_array_size; i++) {
        if (i) printf(" ");
        printf("%d", array_get(array_of_even_numbers, i));
    }
    printf("\n");

    array_delete(array_of_even_numbers);
}

void task2(Array *arr, int shift)
{
    if (!arr) return;

    size_t arr_size = array_size(arr);
    if (arr_size == 0) { printf("\n"); return; }

    if (shift > 0) {
        size_t k = (size_t)shift;
        if (k >= arr_size) {
            for (size_t i = 0; i < arr_size; ++i)
                array_set(arr, i, 0);
        } else {
            for (size_t i = arr_size; i-- > k; )
                array_set(arr, i, array_get(arr, i - k));
            for (size_t i = 0; i < k; ++i)
                array_set(arr, i, 0);
        }
    } else if (shift < 0) {
        size_t k = (size_t)(-shift);
        if (k >= arr_size) {
            for (size_t i = 0; i < arr_size; ++i)
                array_set(arr, i, 0);
        } else {
            for (size_t i = 0; i + k < arr_size; ++i)
                array_set(arr, i, array_get(arr, i + k));
            for (size_t i = arr_size - k; i < arr_size; ++i)
                array_set(arr, i, 0);
        }
    }

    for (size_t i = 0; i < arr_size; i++) {
        if (i) printf(" ");
        printf("%d", array_get(arr, i));
    }
    printf("\n");
}