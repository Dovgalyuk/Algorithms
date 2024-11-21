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

        for (size_t i = 0; i < vector_size(&vec); ++i) {
            int value = vector_get(&vec, i);
            size_t queue_index = (value >> shift) & MASK;
            queues[queue_index].insert(value);
        }

        size_t index = 0;
        for (size_t i = 0; i < RAD; ++i) {
            while (!queues[i].empty()) {
                vector_set(&vec, index++, queues[i].get());
                queues[i].remove();
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    Vector* vec = vector_create();
    int value;
    while (input >> value) {
        vector_resize(vec, vector_size(vec) + 1);
        vector_set(vec, vector_size(vec) - 1, value);
    }
    input.close();

    radix_sort(*vec);

    for (size_t i = 0; i < vector_size(vec); ++i) {
        std::cout << vector_get(vec, i) << std::endl;
    }

    vector_delete(vec);

    return 0;
}
