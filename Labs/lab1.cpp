#include <iostream>
#include <ctime>
#include <climits>
#include "array.h"

using namespace std;

void fill_array(Array* arr) {
    for (int i = 0; i < array_size(arr); i++) {
        array_set(arr,i, rand() % 100 + 1);
    }
}

void sort_array(Array* arr) {
    for (int i = array_size(arr) - 1; i > 0; --i) {
        for (int j = 0; j < i; j++) {
            Data v1 = array_get(arr, j);
            Data v2 = array_get(arr, j + 1);
            if (v1 > v2) {
                array_set(arr, j, v2);
                array_set(arr, j + 1, v1);
            }
        }
    }
}

Array* find_even_numbers(Array* arr) {
    int new_size = 0;
    for (int i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) % 2 == 0) new_size++;
    }
    Array* new_arr = array_create(new_size);
    int j = 0;
    for (int i = 0; i < array_size(arr); i++) {
        int num = array_get(arr, i);
        if (num % 2 == 0) array_set(new_arr, j++, num);
    }
    return new_arr;
}

int main() {
    srand(time(0));
    int size;
    cin >> size;
    Array* arr = array_create(size);
    fill_array(arr);
    Array* even_arr = find_even_numbers(arr);
    sort_array(even_arr);
    int min_diff = INT_MAX;
    for (int i = 0; i < array_size(even_arr) - 1; i++) {
        int diff = array_get(even_arr, i + 1) - array_get(even_arr, i);
        if (min_diff > diff) min_diff = diff;
    }
    cout << min_diff;
    system("pause");
    array_delete(arr);
    array_delete(even_arr);
}

