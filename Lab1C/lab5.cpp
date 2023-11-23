#include <iostream>
#include <map>
#include <chrono>
#include <random>
#include "avl.h"

using namespace std;
using namespace std::chrono;


string generateRandomString(size_t length)
{
    const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> distribution(0, static_cast<int>(CHARACTERS.size() - 1));

    string random_string;
    for (size_t i = 0; i < length; i++)
    {
        random_string += CHARACTERS[distribution(generator)];
    }
    return random_string;
}

//Функция для тестирования вставки в AVL
void testAVLTreeInsertion(int numElements) 
{
    AVLTree tree;
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numElements; i++) 
    {
        string key = generateRandomString(10);
        tree.insert(key, "Value " + key);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "AVLTree Insertion Time: " << duration << " microseconds" << endl;
}

//Функция для тестирования вставки в map
void testMapInsertion(int numElements) 
{
    map<string, string> m;
    auto start = high_resolution_clock::now();

    for (int i = 0; i < numElements; i++) 
    {
        string key = generateRandomString(10);
        m.insert({ key, "Value " + key });
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "map Insertion Time: " << duration << " microseconds" << endl;
}

int main() 
{
    int testSizes[] = { 100, 500, 1000, 10000, 100000, 500000 };
    for (int size : testSizes) 
    {
        cout << "Testing with " << size << " elements:" << endl;
        testAVLTreeInsertion(size);
        testMapInsertion(size);
        cout << endl;
    }
    return 0;
}
