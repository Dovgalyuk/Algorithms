#include "splaytree.h"
#include <iostream>
#include <string>

void addTest(SplayTree& tree, int numElements) {
    for (int i = 0; i < numElements; ++i) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        tree.add(key, value);
    }
}

void findTest(SplayTree& tree, int numElements) {
    int found = 0;
    for (int i = 0; i < numElements; ++i) {
        std::string key = "key" + std::to_string(rand() % numElements);
        std::string result = tree.find(key);
        if (!result.empty()) {
            found++;
        }
        else {
            std::cerr << "Error: Key '" << key << "' not found." << std::endl;
            exit(1);
        }
    }
    std::cout << "Found " << found << " elements." << std::endl;
}

void removeTest(SplayTree& tree, int numElements) {
    for (int i = 0; i < numElements / 2; ++i) {
        std::string key = "key" + std::to_string(rand() % numElements);
        tree.remove(key);
        std::string beforeRemove = tree.find(key);
        if (!beforeRemove.empty()) {
            std::cerr << "Error: removetest" << std::endl;
            exit(1);
        }
    }
}

void stressTest(SplayTree& tree, int numOperations) {
    for (int i = 0; i < numOperations; ++i) {
        int op = rand() % 3;
        std::string key = "key" + std::to_string(rand() % 1000);
        std::string value = "value" + std::to_string(rand() % 1000);

        if (op == 0) {
            tree.add(key, value);
        }
        else if (op == 1) {
            tree.find(key);
        }
        else {
            tree.remove(key);
        }
    }
}

int main() {
    SplayTree tree;
    srand((unsigned)time(0));
    int numElements = 1000;
    int numOperations = 10000;

    std::cout << "Adding test..." << std::endl;
    addTest(tree, numElements);

    std::cout << "Finding test..." << std::endl;
    findTest(tree, numElements);

    std::cout << "Removing test..." << std::endl;
    removeTest(tree, numElements);

    std::cout << "Stress test..." << std::endl;
    stressTest(tree, numOperations);

    return 0;
}