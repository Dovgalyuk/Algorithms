#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include "../LibraryCPP/array.h"

using namespace std;

int sizeArray();

Array *parseNumbers(string input) {
    int n = sizeArray();
    Array *arr = array_create(n);
    stringstream ss(input);
    string token;
    size_t i = 0;
    while (ss >> token && i < n) {
        array_set(arr, i, stoi(token));
        i++;    
    }
    return arr;
}

Array *array_create_and_write()
{
    string str;
    ifstream inF("input.txt");
    if (!inF.is_open()) {
        cout << "Error opening file!" << endl;
        return nullptr;
    }
    getline(inF, str); // пропускаем первую строку (размер)
    getline(inF, str); // читаем вторую строку с числами
    inF.close();
    return parseNumbers(str);
}

void task1(Array *arr){
    if (arr == nullptr) return;
    
    int sum = 0;
    size_t size = array_size(arr);
    for(size_t i = 0; i < size; i++){
        sum += array_get(arr, i);
    }
    cout << "sum = " << sum << '\n';
}

void task2(Array *arr){
    if (arr == nullptr) return;
    
    size_t n = array_size(arr);
    
    // bubble sort
    for(size_t i = 0; i < n - 1; i++){
        for (size_t j = 0; j < n - i - 1; j++){
            if(array_get(arr, j) > array_get(arr, j + 1)){
                // swap
                Data temp = array_get(arr, j);
                array_set(arr, j, array_get(arr, j + 1));
                array_set(arr, j + 1, temp);
            }
        }
    }
    
    cout << "unique numbers: ";
    for(size_t i = 0; i < n; i++){
        if (i == 0 || array_get(arr, i) != array_get(arr, i - 1)) {
            cout << array_get(arr, i) << " ";
        }
    }
    cout << endl;
}

int main(){
    Array *arr = array_create_and_write();
    if (arr != nullptr) {
        task1(arr);
        array_delete(arr);
    }
    
    /* Create another array here */
    arr = array_create_and_write();
    if (arr != nullptr) {
        task2(arr);
        array_delete(arr);
    }
}

int sizeArray(){
    string sizeStr;
    ifstream inF("input.txt");
    if (!inF.is_open()){
        return -1;
    }
    getline(inF, sizeStr);
    inF.close();
    return stoi(sizeStr);
}