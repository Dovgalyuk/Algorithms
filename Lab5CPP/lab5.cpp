#include <iostream>
#include <chrono>
#include <fstream>
#include <unordered_map>
#include "hash_table.h"

struct Ans {
    double insert_duration;
    double get_duration;
    double remove_duration;
    size_t numEntries;
};

Ans testCustomHashTable(size_t numEntries) {
    HashTable hashTable;

    std::string *keys = new std::string[numEntries];
    std::string *values = new std::string[numEntries];
    for (size_t i = 0; i < numEntries; ++i) {
        keys[i] = "key" + std::to_string(i);
        values[i] = "value" + std::to_string(i);
    }

    auto startInsert = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numEntries; ++i) {
        hashTable.insert(keys[i], values[i]);
    }
    auto endInsert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertDuration = endInsert - startInsert;

    auto startGet = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numEntries; ++i) {
        (void) hashTable.get(keys[i]);
    }
    auto endGet = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> getDuration = endGet - startGet;

    auto startRemove = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numEntries; ++i) {
        hashTable.remove(keys[i]);
    }
    auto endRemove = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> removeDuration = endRemove - startRemove;

    delete[] keys;
    delete[] values;

    return Ans{insertDuration.count(), getDuration.count(), removeDuration.count(), numEntries};
}

Ans testUnorderedMap(size_t numEntries) {
    std::unordered_map<std::string, std::string> hashMap;

    std::string *keys = new std::string[numEntries];
    std::string *values = new std::string[numEntries];
    for (size_t i = 0; i < numEntries; ++i) {
        keys[i] = "key" + std::to_string(i);
        values[i] = "value" + std::to_string(i);
    }

    auto startInsert = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numEntries; ++i) {
        hashMap[keys[i]] = values[i];
    }
    auto endInsert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertDuration = endInsert - startInsert;

    auto startGet = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numEntries; ++i) {
        (void) hashMap[keys[i]];
    }
    auto endGet = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> getDuration = endGet - startGet;

    auto startRemove = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numEntries; ++i) {
        hashMap.erase(keys[i]);
    }
    auto endRemove = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> removeDuration = endRemove - startRemove;

    delete[] keys;
    delete[] values;

    return Ans{insertDuration.count(), getDuration.count(), removeDuration.count(), numEntries};
}

int main(int argc, char **argv) {
    int n, step;

    if (argc != 3) {
        std::cout << "Need two file names for saving data (custom_hash and std_hash)\n";
        return 1;
    } 

    std::ofstream customFile(argv[1], std::ios::binary);
    std::ofstream stdFile(argv[2], std::ios::binary);
    if (!customFile.is_open() || !stdFile.is_open()) {
        std::cout << "Could not open files for saving data\n";
        return 1;
    }

    std::cout << "Enter n: ";
    std::cin >> n;
    std::cout << "Enter step: ";
    std::cin >> step;

    for (int i = step; i <= n; i += step) {
        Ans customAns = testCustomHashTable(i);
        customFile.write((char*) &customAns, sizeof(Ans));

        Ans stdAns = testUnorderedMap(i);
        stdFile.write((char*) &stdAns, sizeof(Ans));
    }

    customFile.close();
    stdFile.close();

    return 0;
}
