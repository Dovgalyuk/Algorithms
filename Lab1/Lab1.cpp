#include <iostream>
#include <fstream>
#include <climits>
#include <cstdlib>
#include "array.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        return 1;
    }

    int n;
    in >> n;
    if (n <= 0) {
        std::cout << "\n\n0\n";
        return 0;
    }

    Array<int> arr(n);
    for (int i = 0; i < n; ++i) {
        in >> arr[i];
    }
    in.close();

    bool first = true;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > 0) {
            if (!first) std::cout << ' ';
            std::cout << arr[i];
            first = false;
        }
    }
    std::cout << '\n';

    first = true;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < 0) {
            if (!first) std::cout << ' ';
            std::cout << arr[i];
            first = false;
        }
    }
    std::cout << '\n';

    Array<int> evens(n);
    int even_count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0) {
            evens[even_count++] = arr[i];
        }
    }

    if (even_count < 2) {
        std::cout << "0\n";
        return 0;
    }

    int min_diff = INT_MAX;
    for (int i = 0; i < even_count; ++i) {
        for (int j = i + 1; j < even_count; ++j) {
            if (evens[i] != evens[j]) {
                int diff = std::abs(evens[i] - evens[j]);
                if (diff < min_diff) {
                    min_diff = diff;
                }
            }
        }
    }

    std::cout << (min_diff == INT_MAX ? 0 : min_diff) << '\n';
    return 0;
}