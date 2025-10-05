//
// Created by Mukhammadzakhid Nematzhanov on 27/9/25.
//

void compressArray(int* arr, int n, int a, int b) {
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (!(arr[i] >= a && arr[i] <= b)) {
            arr[k] = arr[i];
            k++;
        }
    }

    for (int i = k; i < n; i++) {
        arr[i] = 0;
    }
}


int maxOddSegment(int* arr, int n) {
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
