#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include "array.h"

Array* array_create_and_read(std::ifstream& input)
{
    size_t n;
    input >> n;

    Array* arr = new Array(n);

    for (size_t i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        arr->set(i, x);
    }
    return arr;
}


Array* array_create_and_random_input(std::ifstream& input, int left, int right) {
    size_t n;
    input >> n;

    Array* arr = new Array(n);

    for (size_t i = 0; i < n; ++i) {
        int random_num = left + rand() % (right - left + 1);
        arr->set(i, random_num);
    }
    return arr;
}


void task1(const Array& arr) {
    double reciprocal_sum = 0.0;
    for (size_t i = 0; i < arr.size(); i++) {
        int resistance = arr.get(i);
        if (resistance != 0) {
            reciprocal_sum += 1.0 / resistance;
        }
    }
    double total_resistance = (reciprocal_sum != 0) ? 1.0 / reciprocal_sum : 0;
    std::cout << "Total parallel resistance: " << total_resistance << '\n';
}

void task2(const Array& arr) {
    std::unordered_map<int, int> frequency;
    for (size_t i = 0; i < arr.size(); ++i) {
        frequency[arr.get(i)]++;
    }

    std::cout << "Unique elements: ";
    for (const auto& pair : frequency) {
        if (pair.second == 1) {
            std::cout << pair.first << " ";
        }
    }
    std::cout << '\n';
}

bool check_output(std::ifstream& output, const Array& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        int num;
        output >> num;
        if (num != arr.get(i)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv) {
    std::srand(std::time(nullptr));

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << "\n";
        return 1;
    }

    Array* arr = array_create_and_read(input);
    task1(*arr);
    delete arr;

    input.clear();
    input.seekg(0);
    arr = array_create_and_read(input);
    task2(*arr);
    delete arr;

    input.close();
    return 0;
}