#include <iostream>
#include <fstream>
#include <../LibraryCPP/array.h>
#include <climits>
using namespace std;

Array *array_create_and_read(ifstream &input) {
    int n;
    input >> n;

    Array* arr = array_create(n);

    for (int i = 0; i < n; i++){
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr, size_t n){
    if (n >= 1) {
        array_set(arr, 0, 0);
    }
    if (n >= 2) {
        array_set(arr, 1, 1);
    }
    for (size_t i = 2; i < n; i++) {
        Data x1 = array_get(arr, i - 1);
        Data x2 = array_get(arr, i - 2);
        array_set(arr, i, x1 + x2);
    }

    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i);
        if (i < array_size(arr) - 1) cout << " ";
    }
    cout << endl;
}

void task2(Array* arr, size_t n){
    int min_dif = INT_MAX;

    for (size_t i = 0; i < n; i++) {
        if (array_get(arr, i) % 2 != 0) continue;
        for (size_t j = i + 1; j < n; j++){
            if (array_get(arr, j) % 2 != 0) continue;
            int dif = abs(array_get(arr, i) - array_get(arr, j));
            if (dif < min_dif) {
                min_dif = dif;
            }
        }
    }

    cout << min_dif << endl;
}

int main(int argc, char **argv) {
    Array *arr = NULL;
    ifstream input(argv[1]);

    // 1 task
    size_t n;
    input >> n;

    arr = array_create(n);

    task1(arr, n);

    array_delete(arr);

    // 2 task
    Array* arr2 = array_create_and_read(input);
    size_t n2 = array_size(arr2);

    task2(arr2, n2);
    array_delete(arr2);

    input.close();
    return 0;
}
