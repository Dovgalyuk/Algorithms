#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include "solutions.h"

struct Data {
    double duration1;
    double duration2;
};

Data measure_execution_time(int n) {
    std::vector<int> numbers;
    std::vector<char> operations;

    numbers.resize(n, 0);
    operations.resize(n - 1, '+');

    auto start1 = std::chrono::high_resolution_clock::now();
    Ans ans1 = solve1(numbers, operations);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;

    auto start2 = std::chrono::high_resolution_clock::now();
    Ans ans2 = solve2(numbers, operations);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;

    if (ans1.value != ans2.value)
        printf("Error\n");

    return Data{duration1.count(), duration2.count()};
}

int main(int argc, char **argv) {
    int n;

     if (argc != 3) {
        std::cout << "Need two file names for saving data\n";
        return 1;
    } 

    std::ofstream file1(argv[1], std::ios::binary);
    std::ofstream file2(argv[2], std::ios::binary);
    if (!file1.is_open() || !file2.is_open()) {
        std::cout << "Could not open files for saving data\n";
        return 1;
    }

    std::cout << "Enter n: ";
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        Data ans = measure_execution_time(i);
        file1.write((char*) &ans.duration1, sizeof(double));
        file2.write((char*) &ans.duration2, sizeof(double));
    }

    file1.close();
    file2.close();

    return 0;
}
