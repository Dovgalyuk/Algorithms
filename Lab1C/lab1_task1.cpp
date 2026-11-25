#include <stdio.h>
#include <stdexcept>
#include "array.h"
#include "asistant.h"

void task1(Array *arr)
{
    if (!arr) return;

    Array *array_of_even_numbers = NULL;
    try {
        size_t arr_size = array_size(arr);

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
    }
    catch (const std::out_of_range& e) {
        fprintf(stderr, "task1: %s\n", e.what());
    }

    array_delete(array_of_even_numbers);
}


int main(int argc, char **argv)
{
    if (argc < 2) return 1;

    FILE *input = fopen(argv[1], "r");
    if (!input) return 1;

    Array *arr = nullptr;

    try {
        arr = array_create_and_read(input);
        if (!arr) { fclose(input); return 1; }
        task1(arr);
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