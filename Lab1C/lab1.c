#include <inttypes.h>
#include <stdio.h>
#include "array.h"

static Array *read_array(FILE *input)
{
    int size;
    if (fscanf(input, "%d", &size) != 1 || size < 0)
        return NULL;
    Array *arr = array_create((size_t)size, NULL);
    if (!arr)
        return NULL;
    for (int i = 0; i < size; ++i) {
        intptr_t value;
        if (fscanf(input, "%" SCNdPTR, &value) != 1) {
            array_delete(arr);
            return NULL;
        }
        array_set(arr, (size_t)i, (Data)value);
    }
    return arr;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    FILE *input = fopen(argv[1], "r");
    if (!input)
        return 1;
    for (int n = 0; n < 2; ++n) {
        Array *arr = read_array(input);
        if (!arr) {
            fclose(input);
            return 1;
        }
        for (size_t i = 0; i < array_size(arr); ++i) {
            if (i)
                putchar(' ');
            printf("%" PRIdPTR, (intptr_t)array_get(arr, i));
        }
        putchar('\n');
        array_delete(arr);
    }
    fclose(input);
    return 0;
}
