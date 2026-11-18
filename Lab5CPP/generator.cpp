#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <file> <count> <asc|desc|rand|random|zigzag>\n";
        return 1;
    }
    std::string filename = argv[1];
    size_t count = std::stoull(argv[2]);
    std::string mode = argv[3];

    std::vector<size_t> order(count);
    for (size_t i = 0; i < count; ++i) order[i] = i;

    std::mt19937 rng(2024);
    if (mode == "rand" || mode == "random") {
        std::shuffle(order.begin(), order.end(), rng);
    } else if (mode == "desc") {
        std::reverse(order.begin(), order.end());
    } else if (mode == "zigzag") {
        std::vector<size_t> z(count);
        size_t l = 0, r = count - 1;
        for (size_t i = 0; i < count; ++i) {
            z[i] = (i % 2 == 0) ? order[l++] : order[r--];
        }
        order = z;
    }

    std::ofstream out(filename);
    if (!out) return 1;
    out << "# pattern=" << mode << "\n";
    for (size_t i = 0; i < count; ++i) {
        out << "ADD key_" << order[i] << " value_" << i << "\n";
    }
    return 0;
}