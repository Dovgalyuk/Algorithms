#include <iostream>
#include <fstream>
#include "array.h"
//сколько из чисел массива кратны хотя бы одному из чисел в диапазоне от 2 до 9
using namespace std;

Array* read_array_from_file(const char* filename)
{
    ifstream input(filename);

    size_t size;
    input >> size;

    Array* arr = array_create(size);

    for (size_t i = 0; i < size; i++)
    {
        Data value;
        input >> value;
        array_set(arr, i, value);
    }

    return arr;
}

int main(int argc, char* argv[]) {
    if (argc < 2) { return 1; }

    Array* arr = read_array_from_file(argv[1]);
    if (!arr) {
        cerr << "Eror open file" << endl;
        return 1;
    }

    int count = 0;
    //O(n^2)
    for (size_t i = 0; i < array_size(arr); i++) {
        int value = array_get(arr, i);
        bool is_multiple = 0;

        for (int j = 2; j <= 9; j++) {
            if (value % j == 0) {
                is_multiple = 1;
                break;
            }
        }

        if (is_multiple) {
            count++;
        }
    }

    cout << count << endl;

    array_delete(arr);
    return 0;
}