#include "Array.hpp"
#include <fstream>
#include <iostream>


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: task2 <input_file> <output_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Ошибка при открытии файла\n";
        return 1;
    }

    size_t n;
    if (!(input >> n) || n == 0) {
        return 0; 
    }

    arr<int> nums(n);
    for (size_t i = 0; i < n; ++i) {
        input >> nums[i];
    }

    size_t repeat = 1;
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] == nums[i - 1]) {
            ++repeat;
        } else {
            output << nums[i - 1] << ' ' << repeat << '\n';
            repeat = 1;
        }
    }
    output << nums[nums.size() - 1] << ' ' << repeat << '\n';

    return 0;
}