#include "array.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void task1(Array* arr)
{
    size_t evenCounter = 0;
    size_t endWithFiveCounter = 0;
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++) {
        array_set(arr, i, rand());
        cout << array_get(arr, i) << ' ';
        if (array_get(arr, i) % 2 == 0) {
            evenCounter++;
        }
        else if (array_get(arr, i) % 10 == 5) {
            endWithFiveCounter++;
        }
        else { continue; }
    }
    cout << "\n Evens: \n" << evenCounter;
    cout << "\n Fives: \n" << endWithFiveCounter;
    return;
}

void task2(Array* arr)
{
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++) {
        array_set(arr, i, rand());
        cout << array_get(arr, i) << ' ';
    }
    size_t min = array_get(arr, 0);
    size_t max = array_get(arr, 0);
    size_t sum = 0;
    
    for (size_t i = 0; i < size; i++) {
        if (array_get(arr, i) < min) {
            min = array_get(arr, i);
        }
        if (array_get(arr, i) > max) {
            max = array_get(arr, i);
        }
    }
    for (size_t i = 0; i < size; i++) {
        sum += array_get(arr, i);
    }
    cout << "\nSum is: \n" << sum - min - max;
    return;
}

int main()
{
    Array* arr = NULL;
    size_t size;
    cin >> size;
    arr = array_create(size);
    task1(arr);
    array_delete(arr);
    cin >> size;
    arr = array_create(size);
    task2(arr);
    array_delete(arr);
}