#include <fstream>
#include <iostream>
#include <map>
#include "array.h"
using namespace std;

Array *arrayCreateFromInput(std::ifstream& input) {
    size_t size;
    input >> size;

    Array* arr = new Array(size);

    for (size_t i = 0; i < size; ++i) {
        int value;
        input >> value;
        arr->set(i, value);
    }
    return arr;
}
Array *DataDayInMonth(){
    Array *monthDay = new Array(12);
    monthDay->set(0, 31);
    monthDay->set(1, 28);
    monthDay->set(2, 31);
    monthDay->set(3, 30);
    monthDay->set(4, 31);
    monthDay->set(5, 30);
    monthDay->set(6, 31);
    monthDay->set(7, 31);
    monthDay->set(8, 30);
    monthDay->set(9, 31);
    monthDay->set(10, 30);
    monthDay->set(11, 31);
    return monthDay;
}

void task1(Array *arr) {
    Array *sumRainfallInMonth = new Array(12);
    Array *dayInMonth = DataDayInMonth();

    int month = 0, day = 1, summ = 0;
    for (size_t i = 0; i < arr->size(); i++) {
        if (day < dayInMonth->get(month)){
            summ += arr->get(i);
            day++;
        } else {
            summ += arr->get(i);
            sumRainfallInMonth->set(month, summ);
            month += 1;
            day = 1;
            summ = 0;
        }
    }
    // Print answer
    for (size_t i = 0; i < 12; i++){
        cout << sumRainfallInMonth->get(i) << " ";
    }
    cout << '\n';
    // Delete array
    delete sumRainfallInMonth;
    delete dayInMonth;
}

void task2(Array *arr) {
    map<int, int> mp;
    for (size_t i = 0; i < arr->size(); i++) {
        mp[arr->get(i)] += 1;
    }

    // Print answer
    map<int, int>::iterator itr;
    for (itr = mp.begin(); itr != mp.end(); ++itr){
        if (itr->second == 2) {
            cout << itr->first << " ";
        }
    }
    cout << '\n';
}


bool testTask1(const Array& arr){
    Array *testArr = new Array(12);
    testArr->set(0, 1504);
    testArr->set(1, 1249);
    testArr->set(2, 1709);
    testArr->set(3, 1464);
    testArr->set(4, 1777);
    testArr->set(5, 1381);
    testArr->set(6, 1497);
    testArr->set(7, 1573);
    testArr->set(8, 1523);
    testArr->set(9, 1549);
    testArr->set(10, 1410);
    testArr->set(11, 1498);
    if (arr.size() == 12) {
        cout << "Size array is not true";
        return false;
    }

    for(size_t i = 0; i < 12; i++) {
        if(testArr->get(i) != arr.get(i)) {
            cout << "Element on index " << i << " not correct";
            return false;
        }
    }
    return true;
}

bool testTask2(const Array& arr){
    Array *testArr = new Array(3);
    testArr->set(0, 1);
    testArr->set(1, 3);
    testArr->set(2, 4);
    if (arr.size() == 3) {
        cout << "Size array is not true";
        return false;
    }

    for(size_t i = 0; i < 12; i++) {
        if(testArr->get(i) != arr.get(i)) {
            cout << "Element on index " << i << " not correct";
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    ifstream input(argv[1]);
    ifstream output(argv[2]);
    Array *arrTask1 = arrayCreateFromInput(input);
    task1(arrTask1);
    // Test output task 1
    if(testTask1(*arrTask1)) {
        return 1;
    }

    Array *arrTask2 = arrayCreateFromInput(input);
    task2(arrTask2);
    // Test output task 2
    if(testTask2(*arrTask2)) {
        return 1;
    }

    // End function
    delete arrTask1;
    delete arrTask2;
    input.close();
    return 0;
}
