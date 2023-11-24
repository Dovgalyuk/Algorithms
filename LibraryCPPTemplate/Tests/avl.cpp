#include "avl.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <random>

using namespace std;
using namespace std::chrono;

string generateRandomString(size_t length) 
{
    const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> distribution(0, static_cast<int>(CHARACTERS.size() - 1));

    string random_string;
    for (size_t i = 0; i < length; ++i) 
    {
        random_string += CHARACTERS[distribution(generator)];
    }
    return random_string;
}

bool isTreeBalanced(AVLTree& tree)
{
    return tree.isBalanced();
}

bool verifyInsertion(AVLTree& tree, string key)
{
    string expectedValue = "Value " + key;
    string actualValue = tree.find(key);
    bool isBalanced = isTreeBalanced(tree);
    return actualValue == expectedValue && isBalanced;
}

bool verifyDeletion(AVLTree& tree, string key)
{
    string value = tree.find(key);
    bool isBalanced = isTreeBalanced(tree);
    return value.empty() && isBalanced;
}

void testInsertion(AVLTree& tree, vector<string> keys)
{
    auto start = high_resolution_clock::now();
    for (auto key : keys)
    {
        //cout << "Inserting key: " << key << endl;
        tree.insert(key, "Value " + key);
        if (!verifyInsertion(tree, key))
        {
            cout << "Insertion failed for key: " << key << endl;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Insertion time for " << keys.size() << " elements: "
        << duration.count() << " microseconds" << endl;
}

void testSearch(AVLTree& tree, const vector<string>& keys)
{
    auto start = high_resolution_clock::now();
    for (auto key : keys)
    {
        //cout << "Searching for key: " << key << endl;
        if (tree.find(key).empty())
        {
            cout << "Search failed for key: " << key << endl;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Search time for " << keys.size() << " elements: "
        << duration.count() << " microseconds" << endl;
}

void testDeletion(AVLTree& tree, const vector<string>& keys)
{
    auto start = high_resolution_clock::now();
    for (auto key : keys)
    {
        //cout << "Deleting key: " << key << endl;
        tree.remove(key);
        if (!verifyDeletion(tree, key))
        {
            cout << "Deletion failed for key: " << key << endl;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Deletion time for " << keys.size() << " elements: "
        << duration.count() << " microseconds" << endl;
}

int main()
{
    const int testSizes[] = { 100, 1000, 10000, 100000 }; // Размеры для тестирования
    const int numTests = sizeof(testSizes) / sizeof(testSizes[0]); // Количество тестов

    for (int i = 0; i < numTests; ++i) {
        AVLTree tree;
        int numElements = testSizes[i];
        vector<string> keys;

        for (int j = 0; j < numElements; j++)
        {
            keys.push_back(generateRandomString(10 + rand() % 10));
        }

        cout << "Testing " << numElements << " elements:" << endl;
        testInsertion(tree, keys);
        testSearch(tree, keys);
        testDeletion(tree, keys);
        cout << endl;
    }

    return 0;
}
