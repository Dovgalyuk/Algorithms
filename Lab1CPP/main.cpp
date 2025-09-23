#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include "array.h"

static int sum_of_digits(const Array& a) {
    int s = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        int v = std::abs(a[i]);
        if (v == 0) continue;
        while (v) { s += v % 10; v /= 10; }
    }
    return s;
}

static int most_frequent(const Array& a) {
    std::unordered_map<int,int> cnt;
    int bestVal = 0, bestCnt = -1;
    for (size_t i = 0; i < a.size(); ++i) {
        int v = a[i];
        int c = ++cnt[v];
        if (c > bestCnt || (c == bestCnt && v < bestVal)) {
            bestCnt = c; bestVal = v;
        }
    }
    return bestVal;
}

int main(int argc, char** argv) {
    std::ifstream fin;
    std::istream* pin = &std::cin;
    if (argc > 1) {
        fin.open(argv[1]);
        if (!fin) {
            std::cerr << "Failed to open file\n";
            return 1;
        }
        pin = &fin;
    }
    std::istream& in = *pin;

    size_t n;
    if (!(in >> n) || n == 0) {
        std::cerr << "Invalid array size\n";
        return 1;
    }

    Array arr(n);
    for (size_t i = 0; i < n; ++i) {
        if (!(in >> arr[i])) {
            std::cerr << "Not enough numbers\n";
            return 1;
        }
    }

    std::cout << "Sum of digits: " << sum_of_digits(arr) << "\n";
    std::cout << "Most frequent: " << most_frequent(arr) << "\n";
    return 0;
}
