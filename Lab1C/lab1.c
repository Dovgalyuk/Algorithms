#include "array.h"
#include <stdio.h>
#include <stdbool.h>

Array *array_create_from_size(FILE *input) {
    int n;
    if (fscanf(input, "%d", &n) != 1) {
        return NULL;
    }
    return array_create(n, NULL);
}

Array *array_create_and_read(FILE *input) {
    int n;
    if (fscanf(input, "%d", &n) != 1) {
        return NULL;
    }

    Array *arr = array_create(n, NULL);
    if (arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; ++i) {
        int x;
        if (fscanf(input, "%d", &x) != 1) {
            array_delete(arr);
            return NULL;
        }
        array_set(arr, i, (Data)x);
    }

    return arr;
}

bool is_palindrome(int num) {
    if (num < 0) return false;
	if (num < 10) return true;
    
    int reversed = 0;
    int original = num;
    
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    
    return original == reversed;
}

void task1(Array *arr) {
    int current = 0;
    for (size_t i = 0; i < array_size(arr); i++) {
        while (!is_palindrome(current)) {
            current++;
        }
        array_set(arr, i, (Data)current);
        printf("%d ", current);
        current++;
    }
}

void task2(Array *arr) {
    for (size_t i = 0; i < array_size(arr); i++) {
        bool is_first = true;
        for (size_t j = 0; j < i; j++) {
            if (array_get(arr, i) == array_get(arr, j)) {
                is_first = false;
                break;
            }
        }
        
        if (is_first) {
            int count = 0;
            for (size_t j = i; j < array_size(arr); j++) {
                if (array_get(arr, i) == array_get(arr, j)) {
                    count++;
                }
            }
            
            if (count == 2) {
                printf("%d ", (int)array_get(arr, i));
            }
        }
    }
}

int main(int argc, char **argv) {
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    
    if (input == NULL) {
        printf("Error: Can't open the input file %s\n", argv[1]);
        return 1;
    }
    
    arr = array_create_from_size(input);
    if (arr != NULL) {
        task1(arr);
        array_delete(arr);
    }
    
    arr = array_create_and_read(input);
    if (arr != NULL) {
        task2(arr);
        array_delete(arr);
    }
        
    fclose(input);
    return 0;
}
