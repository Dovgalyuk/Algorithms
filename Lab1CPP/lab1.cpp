#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "array.h"

using namespace std; 

Array *array_create_and_read(const string& filename){
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Couldn't open this file: " << filename << endl;
        return nullptr;
    }

    size_t new_size;
    inputFile >> new_size;

    Array *arr = array_create(new_size, 0);
    if (!arr){
        return nullptr;
    } 

    for (size_t i = 0; i < new_size; ++i) {
        int number;
        if (!(inputFile >> number)) {
            cerr << "Couldn't read file." << endl;
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, number);
    }

    inputFile.close();
    return arr;
}

void task1(Array* arr) {
    int max = 0;
    int counter = 0;
    for(int i = 0; i<array_size(arr); i++){
        int num = array_get(arr, i);
        if(num>max){
            max = num;
        }
    }

    for(int i = 0;i<array_size(arr);i++){
        int abs_num = array_get(arr, i);
        if(abs(abs_num)>max){
            counter+=1;
        }
    }

    cout << "Result: " << counter;
}

void task2(Array* arr) {
    int a;
    int b;
    size_t index = 0;

    for (int i = 0; i < array_size(arr); ++i) {
        int num = array_get(arr, i);
        if (num < a || num > b) {
            array_set(arr, index++, array_get(arr, i));
        }
    }

    while(index<array_size(arr)){
        array_set(arr, index++, 0);
    }
}

int main() {
    Array* arr1 = array_create_and_read("input_1.txt");
    if (arr1) {
        task1(arr1);
        array_delete(arr1);
    }

    Array* arr2 = array_create_and_read("input_2.txt");
    if (arr2) {
        task2(arr2);
        array_delete(arr2);
    }

    return 0;
}