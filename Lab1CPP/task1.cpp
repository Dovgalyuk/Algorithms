#include "array.h"
#include "task1.h"

int task1(Array* arr) {
    int maxLen = 0;
    int currentLen = 0;

    for (size_t i = 0; i < array_size(arr); i++) {
        int value = array_get(arr, i);
        if (value % 2 != 0) {
            currentLen++;
            if (currentLen > maxLen) {
                maxLen = currentLen;
            }
        } else {
            currentLen = 0;
        }
    }

    return maxLen;
}
