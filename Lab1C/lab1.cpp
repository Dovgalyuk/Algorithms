#include "../LibraryCPP/array.h"
#include <iostream>
#include <ctime> 

using namespace std;

void task1(Array *arr) {
    size_t size = array_size(arr);
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        int value = (int)array_get(arr, i);
        if (value > 0 && value % 2 == 0) {
            sum += value;
        }
    }
    cout << "sum task1 " << sum << endl;
}

void task2(Array *arr) {
    size_t size = array_size(arr);
    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += (int)array_get(arr, i);
    }
    double average = static_cast<double>(sum) / size;
    cout << "ellem < (" << average << "): ";
    for (size_t i = 0; i < size; i++) {
        if ((double)array_get(arr, i) < average) {
            cout << array_get(arr, i) << " ";
        }
    }
    cout << endl;
}

void CreateArray(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand());
}

int main()
{
    srand((unsigned int)time(NULL)); //random
    Array *arr = NULL;
    size_t size;
    
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task1(arr);
    array_delete(arr);

    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task2(arr);
    array_delete(arr);
}