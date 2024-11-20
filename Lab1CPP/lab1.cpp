#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

// sum of the elements is less than 20
int task_1(const Array* arr) {
    int sum = 0;
    for (size_t i = 0; i < array_size(arr); ++i) {
        if (array_get(arr, i) <= 20) {
            sum += array_get(arr, i);
        }
    }
    return sum;
}

// sum_elements between min and max
int task_2(const Array* arr) {
    int sum = 0;
    int min = array_get(arr, 0);
    int max = array_get(arr, 0);
    size_t index_min = 0;
    size_t index_max = 0;

    for (size_t i = 1; i < array_size(arr); ++i) {
        if (array_get(arr, i) < min) {
            min = array_get(arr, i);
            index_min = i;
        }
        if (array_get(arr, i) > max) {
            max = array_get(arr, i);
            index_max = i;
        }
    }
    if (index_min > index_max) {
        swap(index_min, index_max);
    }
    for (size_t i = index_min + 1; i < index_max; ++i) {
        sum += array_get(arr, i);
    }
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Íåîáõîäèìî óêàçàòü èìÿ ôàéëà!" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Îøèáêà îòêðûòèÿ ôàéëà: " << argv[1] << endl;
        return 1;
    }

    int n;
    file >> n;
    Array* arr = array_create(n);

    for (size_t i = 0; i < array_size(arr); ++i) {
        int value;
        file >> value;
        array_set(arr, i, value);
    }
    file.close();

    int sum = task_1(arr);
    cout << "Îòâåò 1: " << sum << endl;
    sum = task_2(arr);
    cout << "Îòâåò 2: " << sum << endl;
    array_delete(arr);

    file.open(argv[1]);
    file >> n;
    arr = array_create(n);

    for (size_t i = 0; i < array_size(arr); ++i) {
        int value;
        file >> value;
        array_set(arr, i, value);
    }
    file.close();

    sum = task_1(arr);
    cout << "Îòâåò 1: " << sum << endl;
    sum = task_2(arr);
    cout << "Îòâåò 2: " << sum << endl;
    array_delete(arr);
    return 0;
}
