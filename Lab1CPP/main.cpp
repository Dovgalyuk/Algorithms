#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "array.h"

static int sum_of_digits(const Array& a) {
    int s = 0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        int v = std::abs(a[i]);
        while (v) { s += v % 10; v /= 10; }
    }
    return s;
}

static int most_frequent(const Array& a) {
    std::vector<int> v(a.size());
    for (std::size_t i = 0; i < a.size(); ++i) v[i] = a[i];
    std::sort(v.begin(), v.end());

    int bestVal = v.empty() ? 0 : v[0], bestCnt = 0;
    int curVal = 0, curCnt = 0;

    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i == 0 || v[i] != curVal) {
            if (curCnt > 0) {
                if (curCnt > bestCnt || (curCnt == bestCnt && curVal < bestVal)) {
                    bestCnt = curCnt; bestVal = curVal;
                }
            }
            curVal = v[i];
            curCnt = 1;
        } else {
            ++curCnt;
        }
    }
    if (curCnt > 0) {
        if (curCnt > bestCnt || (curCnt == bestCnt && curVal < bestVal)) {
            bestCnt = curCnt; bestVal = curVal;
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

    std::size_t n;
    if (!(in >> n) || n == 0) {
        std::cerr << "Invalid array size\n";
        return 1;
    }

    Array arr(n);
    for (std::size_t i = 0; i < n; ++i) {
        if (!(in >> arr[i])) {
            std::cerr << "Not enough numbers\n";
            return 1;
        }
    }

    std::cout << "Sum of digits: " << sum_of_digits(arr)
              << ";Most frequent: " << most_frequent(arr) << "\n";
}
