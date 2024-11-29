#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <set>
#include "Set.h"

struct data {
    double insert, find, remove;
    size_t number;
};

data stdSet(int n) {
    std::set<std::string> set;
    data temp;
    temp.number = n;
    std::string* values = new std::string[n];

    for (int i = 0; i < n; i++) {
        values[i] = std::to_string(i + 1);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        set.insert(values[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> res = end - start;
    temp.insert = res.count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        set.find(values[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.find = res.count();


    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        set.erase(values[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.remove = res.count();

    delete[] values;

    return temp;
}

data mySet(int n) {
    Set set;
    data temp;
    temp.number = n;
    std::string* values = new std::string[n];

    for (int i = 0; i < n; i++) {
        values[i] = std::to_string(i + 1);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        set.insert(values[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> res = end - start;
    temp.insert = res.count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        set.find(values[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.find =  res.count();


    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        set.remove(values[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.remove = res.count();

    delete[] values;

    return temp;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::ofstream outMy("mySet", std::ios::binary);
    std::ofstream outStd("stdSet", std::ios::binary);

    for (int i = 1; i < n; i += 100) {
        data res;
        res = mySet(i + 1);
        outMy.write(reinterpret_cast<char*>(&res), sizeof(data));
        res = stdSet(i + 1);
        outStd.write(reinterpret_cast<char*>(&res), sizeof(data));
    }

    outMy.close();
    outStd.close();

	return 0;
}

