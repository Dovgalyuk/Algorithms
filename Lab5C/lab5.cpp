#include <map>
#include <chrono>
#include <random>
#include <vector>
#include "splaytree.h"
using namespace std;
using namespace std::chrono;

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

// Функция для тестирования вставки в SplayTree
void testSplayTreeInsertion(vector<string> keys) {
    SplayTree tree;
    auto start = high_resolution_clock::now();

    for (auto key : keys) {
        tree.add(key, "Value " + key);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "SplayTree Insertion Time: " << duration << " microseconds" << endl;
}

// Функция для тестирования вставки в map
void testMapInsertion(vector<string> keys) {
    map<string, string> m;
    auto start = high_resolution_clock::now();

    for (auto key : keys) {
        m.insert({ key, "Value " + key });
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "map Insertion Time: " << duration << " microseconds" << endl;
}

int main() {
    int testSizes[] = { 100, 500, 1000, 10000, 100000, 500000 };
    for (int size : testSizes) {
        vector<string> keys;
        for (int i = 0; i < size; i++) {
            keys.push_back(generateRandomString(10));
        }

        cout << "Testing with " << size << " elements:" << endl;
        testSplayTreeInsertion(keys);
        testMapInsertion(keys);
        cout << endl;
    }
    return 0;
}