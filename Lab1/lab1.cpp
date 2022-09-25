#include <iostream>
#include <ctime>
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

int main() {
    srand(time(0));
    int size;
    cin >> size;
    Array* arr = array_create(size);
    fill_array(arr);
    sort_array(arr);
    int n1, n2, last;
    for (int i = 0; i < array_size(arr); i++) {
        Data v = array_get(arr, i);
        if ( v % 2 == 0) {
            n1 = v;
            last = i;
            break;
        }
    }
    for (int i = last + 1; i < array_size(arr); i++) {
        Data v = array_get(arr, i);
        if (v % 2 == 0) {
            n2 = v;
            break;
        }
    }
    cout << n2 - n1;
    system("pause");
    array_delete(arr);
}

