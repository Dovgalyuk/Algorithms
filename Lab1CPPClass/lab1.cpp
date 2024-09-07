#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include "LibraryCPPClass/array.h"

Array& array_create_and_read(std::ifstream& input)
{
    int n;
    input >> n;

    Array arr(n);

    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        arr.set(i, x);
    }
    return arr;
}

Array& array_create_and_random_input(std::ifstream& input, int left, int right) {
    int n;
    input >> n;

    Array arr(n);

    for(int i = 0; i < n; i++) {
        int random_num =  left + rand() % (right - left + 1);
        arr.set(i, random_num);
    }
    return arr;

}

void task1(Array& arr)
{
    Array marks(4); 
    for(size_t i = 0; i < arr.size(); i++) {
        marks.set(arr.get(i)-2, marks.get(arr.get(i)-2) + 1);
    }
    for(size_t i = 0; i < 4; i++) {
        std::cout << "Mark " << i+2 << " : " << marks.get(i) << '\t';
    }
    std::cout << '\n';
}

void task2(Array& arr)
{
    Array frequency(201);

    for (int i = 0; i < arr.size(); ++i) {
        frequency.set(arr.get(i) - 1 + 100, frequency.get(arr.get(i) - 1 + 100) + 1); // frequency[arr[i] - 1 + 100]++;
    }

    int max_frequency = 0;
    int most_frequent_number = INT_MIN;

    for(int i = 0; i < 201; i++) {
        if(frequency.get(i) > max_frequency) {
            max_frequency = frequency.get(i);
            most_frequent_number = i - 100;
        }
    }

    std::cout << most_frequent_number << '\n';
}


//be work for any nums, not only for the segment [-100, 100]
void task2_v2(Array& arr) {
    std::unordered_map<int, int> mp;

    for(int i = 0; i < arr.size(); i++) {
        int num = arr.get(i);
        if(mp.find(num) == mp.end()) {
            mp[num] = 0;
        } else {
            mp[num]++;
        }
    }

    int max_frequency = 0;
    int most_frequent_number = INT_MIN;

    for(auto it : mp) {
        if(it.second > max_frequency) {
            max_frequency = it.second;
            most_frequent_number = it.first;
        }
    }
    std::cout << most_frequent_number << '\n';
}

bool check_output(std::ifstream& output, Array& arr) {
    for(int i = 0; i < arr.size(); i++) {
        int num; 
        output >> num;
        if(num != arr.get(i)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    //For random     
    std::srand(std::time(nullptr));

    // With my tests
    std::ifstream input(argv[1]);
    std::ifstream output(argv[2]);
    if (!input.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << "\n";
        return 1;
    }

    Array arr = array_create_and_read(input);
    task1(arr);
    if(check_output(output, arr)) {
        return 1;
    }
    arr.~Array(); // if we want to explicit call to destructor 

    arr = array_create_and_read(input);
    task2(arr);
    if(check_output(output, arr)) {
        return 1;
    }
    arr.~Array();

    input.close();

    // With random
    std::ifstream input(argv[3]);
    if (!input.is_open()) {
        std::cerr << "Failed to open file: " << argv[3] << "\n";
        return 1;
    }

    Array arr = array_create_and_random_input(input, 2, 5);
    task1(arr);
    arr.~Array();

    arr = array_create_and_random_input(input, -100, 100);
    task2(arr);
    arr.~Array();

    input.close();

    
    return 0;
}