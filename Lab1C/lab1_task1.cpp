#include <cstdio>
#include "array.h"

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    FILE* input = fopen(argv[1], "r");
    if (!input) return 1;

    int n;
    if (fscanf(input, "%d", &n) != 1) { fclose(input); return 1; }

    Array* arr = array_create(n);
    for (int i = 0; i < n; ++i) {
        int x;
        if (fscanf(input, "%d", &x) != 1) { array_delete(arr); fclose(input); return 1; }
        array_set(arr, i, x);
    }
    fclose(input);

    size_t size = array_size(arr);
    if (size == 0) { printf("0.000000\n"); array_delete(arr); return 0; }

    double sum = 0.0;
    for (size_t i = 0; i < size; ++i) {
        int r = array_get(arr, i);
        if (r <= 0) { printf("Error\n"); array_delete(arr); return 0; }
        sum += 1.0 / r;
    }

    printf("%.6f\n", 1.0 / sum);
    array_delete(arr);
    return 0;
}
