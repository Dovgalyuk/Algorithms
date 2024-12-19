#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>

#include "BinaryHeap.h"

struct data {
    double push, pop;
    size_t number;
};

data stdQueue(int n) {
    std::priority_queue<size_t, std::vector<size_t>, std::less<size_t>> queue;
    data temp;
    temp.number = n;
    size_t* values = new size_t[n];

    for (int i = 0; i < n; i++) {
        values[i] = i;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        queue.push(values[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> res = end - start;
    temp.push = res.count();

    delete[] values;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        queue.pop();
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.pop = res.count();

    return temp;
}

bool less(const size_t& a, const size_t& b) {
    return a < b;
}

data myHeap(int n) {
    BinaryHeap<size_t, less> heap;
    data temp;
    temp.number = n;
    size_t* values = new size_t[n];

    for (int i = 0; i < n; i++) {
        values[i] = i;
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        heap.push(values[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> res = end - start;
    temp.push = res.count();

    delete[] values;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; ++i) {
        heap.pop();
    }
    end = std::chrono::high_resolution_clock::now();
    res = end - start;
    temp.pop = res.count();

    return temp;
}

int main() {
    size_t n = 0;
    std::cin >> n;
    std::ofstream outMy("myHeap", std::ios::binary);
    std::ofstream outStd("stdQueue", std::ios::binary);

    for (size_t i = 1; i < n + 2; i += n * 0.01) {
        data res;
        res = myHeap(i + 1);
        outMy.write(reinterpret_cast<char*>(&res), sizeof(data));
        res = stdQueue(i + 1);
        outStd.write(reinterpret_cast<char*>(&res), sizeof(data));
    }

    outMy.close();
    outStd.close();

    return 0;
}
