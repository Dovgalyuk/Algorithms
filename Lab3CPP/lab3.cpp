#include <iostream>
#include <fstream>
#include <cmath>
#include "vector.h"
#include "queue.h"  

#define BITS 2
#define RAD (1 << BITS)
#define MASK (RAD - 1)

void radix_sort(int* arr, size_t size) {
    size_t max_bits = sizeof(int) * 8;
    size_t passes = (max_bits + BITS - 1) / BITS;

    Queue* queues[RAD];
    for (size_t i = 0; i < RAD; ++i) {
        queues[i] = queue_create(); 
    }

    for (size_t pass = 0; pass < passes; ++pass) {
        size_t shift = pass * BITS; 

        // Заполнение очередей
        for (size_t i = 0; i < size; ++i) {
            int value = arr[i];
            size_t queue_index = (value >> shift) & MASK;    
            queue_insert(queues[queue_index], value); 
        }

        
        size_t index = 0;
        for (size_t i = 0; i < RAD; ++i) {
            while (!queue_empty(queues[i])) {
                arr[index++] = queue_get(queues[i]); 
                queue_remove(queues[i]); 
            }
        }
    }

    for (size_t i = 0; i < RAD; ++i) {
        queue_delete(queues[i]); 
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

    size_t size = 0;
    int value;
    while (input >> value) {
        size++;
    }
    input.clear(); 
    input.seekg(0); 

    int* arr = new int[size];
    size_t index = 0;
    while (input >> arr[index++]) {
        
    }
    input.close();
    
    radix_sort(arr, size);  

    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << std::endl;
    }
    delete[] arr;
    return 0;
}
