//
// Created by Mukhammadzakhid Nematzhanov on 9/10/25.
//

#include "task1.h"

int task1(int* arr, int n) {
    int maxLen = 0;
    int currentLen = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0) {
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