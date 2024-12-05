#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Map.h"

struct data {
    double insert, find, remove;
    size_t number; 
};

data stdMap(size_t n) {
    std::map<std::string, std::string> map;
    data time{};
    time.number = n;
    std::vector<std::string> keys(n);
    std::vector<std::string> values(n);

    for (size_t i = 0; i < n; ++i) {
        keys[i] = std::to_string(i + 1);
        values[i] = "value" + keys[i];
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; ++i) {
        map.insert({ keys[i], values[i] });
    }
    auto end = std::chrono::high_resolution_clock::now();
    time.insert = std::chrono::duration<double>(end - start).count();


    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; ++i) {
        (void)map.find(keys[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    time.find = std::chrono::duration<double>(end - start).count();


    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; ++i) {
        map.erase(keys[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    time.remove = std::chrono::duration<double>(end - start).count();

    return time;
}

data myAssociativeArray(size_t n) {
    AssociativeArray array;
    data time{};
    time.number = n;

    std::vector<std::string> keys(n);
    for (size_t i = 0; i < n; ++i) {
        keys[i] = std::to_string(i + 1);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys) {
        array.insert(key, "value" + key);
    }
    auto end = std::chrono::high_resolution_clock::now();
    time.insert = std::chrono::duration<double>(end - start).count();


    start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys) {
        array.find(key);
    }
    end = std::chrono::high_resolution_clock::now();
    time.find = std::chrono::duration<double>(end - start).count();


    start = std::chrono::high_resolution_clock::now();
    for (const auto& key : keys) {
        array.remove(key);
    }
    end = std::chrono::high_resolution_clock::now();
    time.remove = std::chrono::duration<double>(end - start).count();

    return time;
}

void benchmark(size_t numbers) {
    std::ofstream outMyConteyner("associativeArray2.txt", std::ios_base::app);
    std::ofstream outStdMap("stdMap2.txt", std::ios_base::app);

    if (!outMyConteyner.is_open() || !outStdMap.is_open()) {
        std::cerr << "Error opening output files!" << std::endl;
        return;
    }

    data res;

    res = myAssociativeArray(numbers);
    outMyConteyner << res.number << " " << res.insert << " " << res.find << " " << res.remove << "\n";

    res = stdMap(numbers);
    outStdMap << res.number << " " << res.insert << " " << res.find << " " << res.remove << "\n";

    outMyConteyner.close();
    outStdMap.close();
}

int main() {

    for (size_t numbers = 100000; numbers <= 1000000; numbers += 20000) {
        benchmark(numbers);
    }

    return 0;
}