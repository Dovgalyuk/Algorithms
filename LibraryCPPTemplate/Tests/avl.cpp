#include "avl.h"
#include <iostream>
#include <chrono>
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

void testInsertion(AVLTree& tree, int numElements)
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numElements; i++) 
    {
        string key = generateRandomString(10); // Генерация случайного ключа
        tree.insert(key, "Value " + key);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Insertion time for " << numElements << " elements: "
        << duration.count() << " microseconds" << endl;
}

void testSearch(AVLTree& tree, int numElements)
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numElements; i++) 
    {
        string key = generateRandomString(10); // Генерация случайного ключа
        tree.find(key);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Search time for " << numElements << " elements: "
        << duration.count() << " microseconds" << endl;
}

void testDeletion(AVLTree& tree, int numElements)
{
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numElements; i++)
    {
        string key = generateRandomString(10); // Генерация случайного ключа
        tree.remove(key);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Deletion time for " << numElements << " elements: "
        << duration.count() << " microseconds" << endl;
}

int main()
{
    const int testSizes[] = { 100, 1000, 10000, 100000 }; // Размеры для тестирования
    const int numTests = sizeof(testSizes) / sizeof(testSizes[0]); // Количество тестов

    for (int i = 0; i < numTests; ++i) {
        AVLTree tree;
        int numElements = testSizes[i];

        cout << "Testing " << numElements << " elements:" << endl;
        testInsertion(tree, numElements);
        testSearch(tree, numElements);
        testDeletion(tree, numElements);
        cout << endl;
    }

    return 0;
}
