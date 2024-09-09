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


void task1(const Array& arr)
{
    Array marks(4); 
    for(size_t i = 0; i < arr.size(); i++) {
        marks.set(arr.get(i)-2, marks.get(arr.get(i)-2) + 1); // marks[arr[i] - 2]++;
    }
    for(size_t i = 0; i < 4; i++) {
        std::cout << "Mark " << i+2 << " : " << marks.get(i) << '\t';
    }
    std::cout << '\n';
}

void task2(const Array& arr)
{
    int min_value = INT_MAX;
    int max_value = INT_MIN;

    for (size_t i = 0; i < arr.size(); ++i) {
        int current = arr.get(i);
        if (current < min_value) min_value = current;
        if (current > max_value) max_value = current;
    }

    size_t frequency_size = max_value - min_value + 1;
    Array frequency(frequency_size);

    for (size_t i = 0; i < arr.size(); ++i) {
        int index = arr.get(i) - min_value; 
        frequency.set(index, frequency.get(index) + 1);
    }

    int max_frequency = 0;
    int most_frequent_number = min_value;

    for (size_t i = 0; i < frequency_size; ++i) {
        if (frequency.get(i) > max_frequency) {
            max_frequency = frequency.get(i);
            most_frequent_number = i + min_value; 
        }
    }

    std::cout << most_frequent_number << '\n';
}



//be work for any nums, not only for the segment [-100, 100]
void task2_v2(const Array& arr) {
    std::unordered_map<int, int> mp;

    for(size_t i = 0; i < arr.size(); i++) {
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

bool check_output(std::ifstream& output, const Array& arr) {
    for(size_t i = 0; i < arr.size(); i++) {
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

    Array* arr = array_create_and_read(input);
    task1(*arr);
    if(check_output(output, *arr)) {
        return 1;
    }
    delete arr;

    arr = array_create_and_read(input);
    task2(*arr);
    if(check_output(output, *arr)) {
        return 1;
    }
    delete arr;
    input.close();

    // With random
    std::ifstream randomInput(argv[3]);
    if (!randomInput.is_open()) {
        std::cerr << "Failed to open file: " << argv[3] << "\n";
        return 1;
    }

    arr = array_create_and_random_input(randomInput, 2, 5);
    task1(*arr);
    delete arr;

    arr = array_create_and_random_input(randomInput, -100, 100);
    task2(*arr);
    delete arr;

    randomInput.close();

    
    return 0;
}
