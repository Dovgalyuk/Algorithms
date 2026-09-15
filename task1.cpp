#include "Array.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: task1 <input_file> <output_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error opening files\n";
        return 1;
    }

    size_t n;
    if (!(input >> n)) {
        return 1;
    }

    arr<int> nums(n);
    for (size_t i = 0; i < n; ++i) {
        input >> nums[i];
    }

    int two = 0, three = 0, four = 0, five = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] == 2) ++two;
        else if (nums[i] == 3) ++three;
        else if (nums[i] == 4) ++four;
        else if (nums[i] == 5) ++five;
    }

    output << "5: " << five << '\n';
    output << "4: " << four << '\n';
    output << "3: " << three << '\n';
    output << "2: " << two << '\n';

    return 0;
}