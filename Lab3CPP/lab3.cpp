#include <iostream>
#include <fstream>
#include <cmath>
#include "vector.h" 
#include "queue.h"  

#define BITS 2
#define RAD (1 << BITS)
#define MASK (RAD - 1)

void radix_sort(Vector& vec) {
    size_t max_bits = sizeof(int) * 8;
    size_t passes = (max_bits + BITS - 1) / BITS;

    Queue queues[RAD];

    for (size_t pass = 0; pass < passes; ++pass) {
        size_t shift = pass * BITS;

        for (size_t i = 0; i < vec.size(); ++i) {
            int value = vec.get(i);
            size_t queue_index = (value >> shift) & MASK;
            queues[queue_index].insert(value);
        }

        size_t index = 0;
        for (size_t i = 0; i < RAD; ++i) {
            while (!queues[i].empty()) {
                vec.set(index++, queues[i].get());
                queues[i].remove();
            }
        }
    }
}

int main(__attribute__((unused)) int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    Vector vec;
    int value;
    while (input >> value) {
        vec.push_back(value);
    }
    input.close();

    radix_sort(vec);

    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec.get(i) << std::endl;
    }

    return 0;
}