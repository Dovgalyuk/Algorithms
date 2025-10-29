#include <iostream>
#include <fstream>
#include <climits>
#include "array.h"

void task1(const char* filename) {
    std::ifstream in(filename);
    int n;
    in >> n;
    array<int> arr(n);
    for (int i = 0; i < n; ++i) {
        in >> arr[i];
    }
    in.close();

    int pos_count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0) ++pos_count;
    }
    bool first = true;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0) {
            if (!first) std::cout << " ";
            std::cout << arr[i];
            first = false;
        }
    }
    std::cout << "\n";

    int neg_count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < 0) ++neg_count;
    }
    first = true;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < 0) {
            if (!first) std::cout << " ";
            std::cout << arr[i];
            first = false;
        }
    }
    std::cout << "\n";
}

void task2(const char* filename) {
    std::ifstream in(filename);
    int n;
    in >> n;
    array<int> arr(n);
    for (int i = 0; i < n; ++i) {
        in >> arr[i];
    }
    in.close();

    array<int> evens(n);
    int even_count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0) {
            evens[even_count++] = arr[i];
        }
    }

    if (even_count < 2) {
        std::cout << "0\n";
        return;
    }

    int min_diff = INT_MAX;
    for (int i = 0; i < even_count; ++i) {
        for (int j = i + 1; j < even_count; ++j) {
            if (evens[i] != evens[j]) {
                int diff = evens[i] - evens[j];
                if (diff < 0) diff = -diff;
                if (diff < min_diff) {
                    min_diff = diff;
                }
            }
        }
    }

    if (min_diff == INT_MAX) {
        std::cout << "0\n";
    }
    else {
        std::cout << min_diff << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }
    task1(argv[1]);
    task2(argv[2]);
    return 0;
}