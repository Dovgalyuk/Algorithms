#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

#include "array.h"

static int sum_digits_int(int x) {
    long long v = x;
    if (v < 0) v = -v;
    int s = 0;
    while (v > 0) {
        s += static_cast<int>(v % 10);
        v /= 10;
    }
    return s;
}

static int sum_of_digits(const Array& a) {
    int sum = 0;
    for (std::size_t i = 0; i < a.size(); ++i) sum += sum_digits_int(a.get(i));
    return sum;
}

static int most_frequent(const Array& a) {
    if (a.size() == 0) return 0;

    std::vector<int> v;
    v.reserve(a.size());
    for (std::size_t i = 0; i < a.size(); ++i) v.push_back(a.get(i));
    std::sort(v.begin(), v.end());

    int bestVal = v[0], bestCnt = 1;
    int curVal  = v[0], curCnt  = 1;

    for (std::size_t i = 1; i < v.size(); ++i) {
        if (v[i] == curVal) {
            ++curCnt;
        } else {
            if (curCnt > bestCnt) {
                bestCnt = curCnt;
                bestVal = curVal;
            }
            curVal = v[i];
            curCnt = 1;
        }
    }
    if (curCnt > bestCnt) {
        bestCnt = curCnt;
        bestVal = curVal;
    }
    return bestVal;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: Lab1CPP <input-file>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "File not found\n";
        return 1;
    }

    long long m = 0;
    if (!(in >> m) || m <= 0) {
        std::cerr << "Invalid array size\n";
        return 1;
    }
    std::size_t n = static_cast<std::size_t>(m);

    Array arr(n);
    for (std::size_t i = 0; i < n; ++i) {
        int value;
        if (!(in >> value)) {
            std::cerr << "Not enough numbers\n";
            return 1;
        }
        arr.set(i, value);
    }

    std::cout << "Sum of digits: " << sum_of_digits(arr)
              << ";Most frequent: " << most_frequent(arr) << "\n";
}