#include <iostream>
#include <string>
#include <unordered_set>
#include <chrono>
#include "myContainer.h"

using namespace std;

const int MIN_KOLICHESTVO_OBHODOV = 100;
const int MAX_KOLICHESTVO_OBHODOV = 5000;
const int SHAG_OBHODA = 700;

int myContainerVSUnorderedSet(int size)
{
    auto myContainer = new container<int, string>(size);
    unordered_set <string> UnorderedSet;

    auto start = chrono::system_clock::now();
    for (int i = 0; i < size; i++) {
        myContainer->insert(to_string(i));
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> myContainerTime = end - start;
    cout << "\tAdding to the myContainer took " << myContainerTime.count() << " seconds." << "\n";
    start = chrono::system_clock::now();
    for (int i = 0; i < size; i++) {
        UnorderedSet.insert(to_string(i));
    }
    end = chrono::system_clock::now();
    chrono::duration<double> UnorderedSetTime = end - start;
    cout << "\tAdding to the UnorderedSet took " << UnorderedSetTime.count() << " seconds." << "\n";

    myContainer->~container();
    UnorderedSet.clear();
    return 0;
}

int main() {
    int shetchik = 1;
    for (int i = MIN_KOLICHESTVO_OBHODOV; i <= MAX_KOLICHESTVO_OBHODOV; i = i + SHAG_OBHODA) {
        cout << "Test " << (char)252 << shetchik << ", kolichestvo elementov: " << i << ":\n";
        myContainerVSUnorderedSet(i);
        cout << "\n";
        shetchik++;
    }
    return 0;
}


