#include "array.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: task1 <input> <output>\n";
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
        out << "0\n\n";
        return 0;
    }

    int mn = a[0], mx = a[0];
    for (std::size_t i = 1; i < n; ++i) {
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
    }

    double avg = (static_cast<double>(mn) + static_cast<double>(mx)) / 2.0;

    std::size_t count = 0;
    std::string indices;
    for (std::size_t i = 0; i < n; ++i) {
        if (a[i] < avg) {
            ++count;
            if (!indices.empty()) indices += ' ';
            indices += std::to_string(i);
        }
    }

    out << count << '\n' << indices << '\n';
    return 0;
}