#include "splaytree.h"
#include <iostream>
#include <string>
#include <random>
#include <vector>
 
using namespace std;
string generateRandomString(size_t length) {
    const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> distribution(0, static_cast<int>(CHARACTERS.size() - 1));

    string random_string;
    for (size_t i = 0; i < length; i++) {
        random_string += CHARACTERS[distribution(generator)];
    }
    return random_string;
}
void addTest(SplayTree *tree, vector<string> keys) {
    for (auto keyy : keys) {
        std::string key = "key" + keyy;
        std::string value = "value" + keyy;
        tree->add(key, value);
        std::string beforeAdd = tree->find(key);
        if (beforeAdd.empty()) {
            std::cerr << "Error: addtest" << std::endl;
            exit(1);
        }
    }
}

void findTest(SplayTree *tree, vector<string> keys) {
    int found = 0;
    for (auto keyy : keys) {
        std::string key = "key" + keyy;
        std::string result = tree->find(key);
        if (!result.empty()) {
            found++;
        }
        else {
            std::cerr << "Error: findtest" << std::endl;
            exit(1);
        }
    }
    std::cout << "Found " << found << " elements." << std::endl;
}

void removeTest(SplayTree *tree, vector<string> keys) {
    for (auto keyy : keys) {
        std::string key = "key" + keyy;
        tree->remove(key);
        std::string beforeRemove = tree->find(key);
        if (!beforeRemove.empty()) {
            std::cerr << "Error: removetest" << std::endl;
            exit(1);
        }
    }
}

void stressTest(SplayTree *tree, int numOperations) {
    for (int i = 0; i < numOperations; ++i) {
        int op = rand() % 3;
        std::string key = "key" + std::to_string(rand() % 1000);
        std::string value = "value" + std::to_string(rand() % 1000);

        if (op == 0) {
            tree->add(key, value);
        }
        else if (op == 1) {
            tree->find(key);
        }
        else {
            tree->remove(key);
        }
    }
}

int main() {
    SplayTree tree;
    srand((unsigned)time(0));
    int numElements = 1000;
    vector<string> keys;
    for (int i = 0; i < numElements; i++) {
        keys.push_back(generateRandomString(10));
    }
    std::cout << "Adding test..." << std::endl;
    addTest(&tree, keys);

    std::cout << "Finding test..." << std::endl;
    findTest(&tree, keys);

    std::cout << "Removing test..." << std::endl;
    removeTest(&tree, keys);


    return 0;
}