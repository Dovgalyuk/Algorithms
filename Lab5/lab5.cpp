#include "my_hash.h" 
#include "blum_filter.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono> 
#include <vector>
#include <unordered_set>

void testBlumFilterTime(std::ofstream& output, size_t num) {
    BloomFilter filter(num, 0.01);

    // Generating data
    std::vector<std::string> data(num);
    for(size_t i = 0; i < num; i++) {
        data[i] = "element_" + std::to_string(i) + "__";
    }

    // Inserting
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num; ++i) {
        filter.insert(data[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> res = end - start;
    output << res.count() << std::endl;

    // Founding
    start = std::chrono::high_resolution_clock::now();
    size_t found_count = 0;
    for (const auto& item : data) {
        if (filter.contains(item)) {
            ++found_count;
        }
    }
    end = std::chrono::high_resolution_clock::now();

    res = end - start;
    output << res.count()  << std::endl;

    size_t false_positives = 0;
    for (size_t i = num; i < num * 2; ++i) {
        if (filter.contains("e" + std::to_string(i))) {
            ++false_positives;
        }
    }
    output << false_positives << std::endl;

    // Removing
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num; ++i) {
        filter.remove(data[i]);
    }
    end = std::chrono::high_resolution_clock::now();

    res = end - start;
    output << res.count()  << std::endl;
}

void testSetTime(std::ofstream& output, size_t num) {
    std::unordered_set<std::string> set;

    // Generating data
    std::vector<std::string> data(num);
    for(size_t i = 0; i < num; i++) {
        data[i] = "e" + std::to_string(i) + "__";
    }

    // Inserting
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num; ++i) {
        set.insert(data[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> res = end - start;
    output << res.count() << std::endl;

    // Founding
    start = std::chrono::high_resolution_clock::now();
    size_t found_count = 0;
    for (const auto& item : data) {
        if (set.find(item) != set.end()) {
            ++found_count;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    
    res = end - start;
    output << res.count() << std::endl;

    // Removing
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < num; ++i) {
        set.erase(data[i]);
    }
    end = std::chrono::high_resolution_clock::now();

    res = end - start;
    output << res.count() << std::endl;
}



int main(int argc, char **argv) {

    std::ofstream output1(argv[1]);
    if (!output1.is_open()) {
        std::cerr << "Failed to open output1 file: " << argv[1] << "\n";
        return 1;
    }

    std::ofstream output2(argv[2]);
    if (!output2.is_open()) {
        std::cerr << "Failed to open output2 file: " << argv[2] << "\n";
        return 1;
    }

    for(size_t i = 100'000; i <= 1'000'000; i+= 10'000) {
        testBlumFilterTime(output1, i);
        testSetTime(output2, i);
    }

    output1.close();
    output2.close();
    

}