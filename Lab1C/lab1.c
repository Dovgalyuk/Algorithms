#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1) {
        return NULL;
    }
    /* Create array */
    Array *arr = array_create(n, NULL);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) != 1) {
            array_delete(arr);
            return NULL;
        }
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
	size_t n = array_size(arr);
	if (n == 0) { printf("0\n"); return; }

	size_t min_idx = 0, max_idx = 0;
	Data min_val = array_get(arr, 0), max_val = array_get(arr, 0);

	for (size_t i = 1; i < n; ++i) {
		Data v = array_get(arr, i);
		if (v < min_val) { min_val = v; min_idx = i; }
		if (v > max_val) { max_val = v; max_idx = i; }
	}

	long sum = 0;
	size_t start = (min_idx < max_idx) ? min_idx + 1 : max_idx + 1;
	size_t end = (min_idx < max_idx) ? max_idx : min_idx;
	for (size_t i = start; i < end; ++i) {
		sum += (long)array_get(arr, i);
	}

	printf("%ld\n", sum);
}

void task2(Array *arr, FILE *input)
{
	int a, b;
	if (fscanf(input, "%d %d", &a, &b) != 2) return;
	if (a > b) { int t = a; a = b; b = t; }

	size_t n = array_size(arr);
	size_t write_pos = 0;

    for (size_t i = 0; i < n; ++i) {
        long long v = (long long)array_get(arr, i);
        if (v < a || v > b) {
            array_set(arr, write_pos++, (Data)v);
        }
    }
	while (write_pos < n) {
		array_set(arr, write_pos++, (Data)0);
	}

    for (size_t i = 0; i < n; ++i) {
        if (i > 0) printf(" ");
        printf("%lld", (long long)array_get(arr, i));
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input>\n", argv[0]); 
        return 1; 
    
    }
    FILE *input = fopen(argv[1], "r");
    if (!input) { 
        perror("fopen"); 
        return 1; 
    }

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr, input);
    array_delete(arr);
    fclose(input);
}
