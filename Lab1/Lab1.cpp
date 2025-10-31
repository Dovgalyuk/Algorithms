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

    int pos_count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr.get(i) > 0) ++pos_count;
    }
    Array<int> pos_arr(pos_count);
    int pi = 0;
    for (int i = 0; i < n; ++i) {
        if (arr.get(i) > 0) {
            pos_arr.set(pi++, arr.get(i));
        }
    }

    int neg_count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr.get(i) < 0) ++neg_count;
    }
    Array<int> neg_arr(neg_count);
    int ni = 0;
    for (int i = 0; i < n; ++i) {
        if (arr.get(i) < 0) {
            neg_arr.set(ni++, arr.get(i));
        }
    }

    for (size_t i = 0; i < pos_arr.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << pos_arr.get(i);
    }
    std::cout << '\n';

    for (size_t i = 0; i < neg_arr.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << neg_arr.get(i);
    }
    std::cout << '\n';

    Array<int> evens(n);
    int even_count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr.get(i) % 2 == 0) {
            evens.set(even_count++, arr.get(i));
        }
    }

    if (even_count < 2) {
        std::cout << "0\n";
        return 0;
    }

    int min_diff = INT_MAX;
    for (int i = 0; i < even_count; ++i) {
        for (int j = i + 1; j < even_count; ++j) {
            if (evens.get(i) != evens.get(j)) {
                int diff = std::abs(evens.get(i) - evens.get(j));
                if (diff < min_diff) {
                    min_diff = diff;
                }
            }
        }
    }

    std::cout << (min_diff == INT_MAX ? 0 : min_diff) << '\n';
    return 0;
}