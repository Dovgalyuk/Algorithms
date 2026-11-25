#include <stdio.h>
#include <stdexcept>
#include "array.h"
#include "asistant.h"

void task2(Array *arr, int shift)
{
    if (!arr) return;

    try {
        size_t arr_size = array_size(arr);
        if (arr_size == 0) { 
            printf("\n");
            return; 
        }

        if (shift > 0) {
            size_t k = (size_t)shift;
            if (k > arr_size) k = arr_size;
            for (size_t i = arr_size; i-- > k;)
                array_set(arr, i, array_get(arr, i - k));
            for (size_t i = 0; i < k; i++)
                array_set(arr, i, 0);
        } else if (shift < 0) {
            size_t k = (size_t)(-shift);
            if (k > arr_size) k = arr_size;
            for (size_t i = 0; i + k < arr_size; i++)
                array_set(arr, i, array_get(arr, i + k));
            for (size_t i = arr_size - k; i < arr_size; i++)
                array_set(arr, i, 0);
        }

        for (size_t i = 0; i < arr_size; i++) {
            if (i) printf(" ");
            printf("%d", array_get(arr, i));
        }
        printf("\n");
    }
    catch (const std::exception& e) {
        fprintf(stderr, "task2: %s\n", e.what());
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) return 1;

    FILE *input = fopen(argv[1], "r");
    if (!input) return 1;

    int shift;
    if (fscanf(input, "%d", &shift) != 1) {
        fclose(input);
        return 1;
    }

    Array *arr = nullptr;
    
    try {
        arr = array_create_and_read(input);
        if (!arr) { fclose(input); return 1; }

        task2(arr, shift);
    }
    catch (const std::exception& e) {
        fprintf(stderr, "Error: %s\n", e.what());
        array_delete(arr);
        fclose(input);
        return 1;
    }

    array_delete(arr);
    fclose(input);
    return 0;
}