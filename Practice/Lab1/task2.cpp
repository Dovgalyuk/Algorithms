#include "array.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: task2 <input> <output>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in) { std::cerr << "Cannot open input\n"; return 1; }
    std::ofstream out(argv[2]);
    if (!out) { std::cerr << "Cannot open output\n"; return 1; }

    std::size_t n = 0;
    if (!(in >> n)) { std::cerr << "Bad size\n"; return 1; }

    Array<int> a(n);
    for (std::size_t i = 0; i < n; ++i) {
        if (!(in >> a[i])) { std::cerr << "Bad element\n"; return 1; }
    }

    if (n == 0) {
        out << "empty\n";
        return 0;
    }

    // Подсчёт частот за O(N) — диапазон 0..1000
    constexpr int MAXV = 1000;
    Array<int> freq(MAXV + 1);
    for (int& v : freq) v = 0;

    for (std::size_t i = 0; i < n; ++i) {
        int v = a[i];
        if (v < 0 || v > MAXV) {
            std::cerr << "Value out of range\n";
            return 1;
        }
        ++freq[static_cast<std::size_t>(v)];
    }

    int best_value = 0;
    int best_count = -1;
    // при равенстве берём наименьшее значение
    for (int v = 0; v <= MAXV; ++v) {
        if (freq[static_cast<std::size_t>(v)] > best_count) {
            best_count = freq[static_cast<std::size_t>(v)];
            best_value = v;
        }
    }

    out << best_value << ' ' << best_count << '\n';
    return 0;
}