#include <iostream>
#include <chrono>
#include <cassert>
#include "hash_table.h"

void loadTest(size_t numEntries) {
    HashTable hashTable;

    auto startInsert = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numEntries; ++i) {
        hashTable.insert("key" + std::to_string(i), "value" + std::to_string(i));
    }
    auto endInsert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertDuration = endInsert - startInsert;
    std::cout << "Time taken to insert " << numEntries << " entries: " << insertDuration.count() << " [" << insertDuration.count() / numEntries << "] " << " seconds." << std::endl;

    auto startGet = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numEntries; ++i) {
        assert(hashTable.get("key" + std::to_string(i)) == "value" + std::to_string(i));
    }
    auto endGet = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> getDuration = endGet - startGet;
    std::cout << "Time taken to get " << numEntries << " entries: " << getDuration.count() << " [" << getDuration.count() / numEntries << "] " << " seconds." << std::endl;

    auto startRemove = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < numEntries; ++i) {
        hashTable.remove("key" + std::to_string(i));
    }
    auto endRemove = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> removeDuration = endRemove - startRemove;
    std::cout << "Time taken to remove " << numEntries << " entries: " << removeDuration.count() << " [" << removeDuration.count() / numEntries << "] " << " seconds." << std::endl;
}

int main() {
    for (int i = 10000; i <= 1000000; i += 10000) {
        loadTest(i);
        std::cout << "\n\n";
    }

    return 0;
}
