#include <fstream>
#include <iostream>
#include "array.h"
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        return 1;
    }

    size_t size = 0;
    input >> size;

    Array<int> numbers(size);

    for (size_t i = 0; i < size; i++) {
        int value = 0;
        input >> value;
        numbers.set(i, value);
    }
    int a = 0;
    int b = 0;
    input >> a >> b;
    size_t write_index = 0;
    for (size_t i = 0; i < size; i++) {
        int value = numbers.get(i);
        if (value < a || value > b) {
            numbers.set(write_index, value);
            write_index++;
        }
    }

    for (size_t i = write_index; i < size; i++) {
        numbers.set(i, 0);
    }

    for (size_t i = 0; i < size; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << numbers.get(i);
    }
    cout << "\n";
}
