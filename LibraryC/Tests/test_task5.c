#include "../array.h"
#include <assert.h>
#include <stdio.h>

void test_task5() {
    Array* arr = array_create(10);
    for (int i = 0; i < 10; i++) {
        array_set(arr, i, i + 1);
    }
    
    int start_index = -1;
    int max_sum = 0;
    
    if (arr->size >= 5) {
        for (size_t i = 0; i <= arr->size - 5; i++) {
            int sum = 0;
            for (size_t j = 0; j < 5; j++) {
                sum += arr->data[i + j];
            }
            
            if (sum > max_sum || start_index == -1) {
                max_sum = sum;
                start_index = i;
            }
        }
    }
    
    assert(max_sum == 40);
    assert(start_index == 5);
    array_destroy(arr);
    printf("Test task5 passed!\n");
}

int main() {
    test_task5();
    return 0;
}