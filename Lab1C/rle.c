#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "array.h"

static Array *read_array(FILE *input)
{
    long long input_size;
    if (fscanf(input, "%lld", &input_size) != 1 || input_size < 0
        || (unsigned long long)input_size > SIZE_MAX)
    {
        return NULL;
    }

    const size_t size = (size_t)input_size;
    Array *arr = array_create(size, NULL);
    if (arr == NULL)
        return NULL;

    for (size_t i = 0; i < size; ++i)
    {
        int value;
        if (fscanf(input, "%d", &value) != 1)
        {
            array_delete(arr);
            return NULL;
        }
        array_set(arr, i, (Data)value);
    }

    return arr;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Cannot open input file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    Array *arr = read_array(input);
    fclose(input);
    if (arr == NULL)
    {
        fprintf(stderr, "Invalid input data\n");
        return EXIT_FAILURE;
    }

    const size_t size = array_size(arr);
    if (size != 0)
    {
        int current = (int)array_get(arr, 0);
        size_t count = 1;

        for (size_t i = 1; i < size; ++i)
        {
            const int value = (int)array_get(arr, i);
            if (value == current)
            {
                ++count;
            }
            else
            {
                printf("%d %zu\n", current, count);
                current = value;
                count = 1;
            }
        }
        printf("%d %zu\n", current, count);
    }

    array_delete(arr);
    return EXIT_SUCCESS;
}
