#include <iostream>
#include "array.h"

using namespace std;

void Random(Array* arr){
    for(size_t i = 0; i < array_size(arr); i++){
        array_set(arr, i, rand() % 100);
    }
}
void task1(Array* arr) {
    Random(arr);
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << '\t';
    }
    cout << '\n';
    double sum = 0;
    for(size_t i = 0; i < array_size(arr); i++){
        sum += array_get(arr, i);
    }
    sum /=array_size(arr);
    cout << "Avg: " <<sum <<'\n';
}
void task2(Array* arr) {
    Random(arr);
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << '\t';
    }
    cout << '\n';
    int diff = 100, timed = 0;
    size_t ArraySize = array_size(arr);
    for (size_t i = 0; i < ArraySize; i++) {
        int Number = array_get(arr, i);
        if (Number % 2 == 0) {
            timed = Number;
            for (size_t j = i + 1; j < ArraySize; j++) {
                int nextNumber = array_get(arr, j);
                if (nextNumber % 2 == 0 && timed <= nextNumber) {
                    int x = nextNumber - timed;
                    if (diff > x && x != 0) {
                        diff = x;
                    }
                }
                else if (nextNumber % 2 == 0 && timed > nextNumber) {
                    int x = timed - nextNumber;
                    if (diff > x && x != 0) {
                        diff = x;
                    }
                }
            }
        }
    }
    if (diff == 100) {
        cout << "Array doesn't have even num" << '\n';
    }
    else {
        cout << "Min diff between even num: " << diff << '\n';
    }
} 

int main()
{
    Array* arr = NULL;
    size_t size;

    cin >> size;
    arr = array_create(size);
    task1(arr);
    array_delete(arr);
    arr = NULL;

    cin >> size;
    arr = array_create(size);
    task2(arr);
    array_delete(arr);
}
