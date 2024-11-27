#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
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
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; ++i) {
        set.insert(std::to_string(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> res = end - start;
    temp.insert = res.count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; ++i) {
        set.find(std::to_string(i));
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.find = res.count();


    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; ++i) {
        set.erase(std::to_string(i));
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.remove = res.count();

    return temp;
}

data mySet(int n) {
    Set set;
    data temp;
    temp.number = n;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; ++i) {
        set.insert(std::to_string(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> res = end - start;
    temp.insert = res.count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; ++i) {
        set.find(std::to_string(i));
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.find =  res.count();


    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; ++i) {
        set.remove(std::to_string(i));
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.remove = res.count();

    return temp;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::ofstream outMy("mySet", std::ios::binary);
    std::ofstream outStd("stdSet", std::ios::binary);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i < n; i += 100) {
        system("cls");
        std::cout << "Current n value: " << i << '\n';
        data res;
        res = mySet(i + 1);
        outMy.write(reinterpret_cast<char*>(&res), sizeof(data));
        res = stdSet(i + 1);
        outStd.write(reinterpret_cast<char*>(&res), sizeof(data));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> res = end - start;
    std::cout << "Time left: " << res.count() << " seconds" << std::endl;

    outMy.close();
    outStd.close();

	return 0;
}

