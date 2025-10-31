#include "../array.h"
#include <assert.h>
#include <stdio.h>

void test_task4() {
    Array* arr = array_create(5);
    array_set(arr, 0, 1);
    array_set(arr, 1, 5);
    array_set(arr, 2, 3);
    array_set(arr, 3, 8);
    array_set(arr, 4, 2);
    
    int count = 0;
    if (arr->size > 0) {
        int max_val = arr->data[0];
        for (size_t i = 1; i < arr->size; i++) {
            if (arr->data[i] > max_val) {
                max_val = arr->data[i];
            }
        }
        
        for (size_t i = 0; i < arr->size; i++) {
            if (abs(arr->data[i]) > max_val) {
                count++;
            }
        }
    }
    
    assert(count == 0);
    array_destroy(arr);
    printf("Test task4 passed!\n");
}

int main() {
    test_task4();
    return 0;
}