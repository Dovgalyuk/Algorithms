#include "apfel.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

static void process_task2(Array* arr, ostream& out) {
    size_t size = array_size(arr);
    bool first = true;
    for (size_t i = 0; i < size; ++i) {
        Data elem = array_get(arr, i);
        if (elem <= 0) {
            throw invalid_argument("Non-positive element found");
        }
        bool divisible = false;
        for (size_t j = 0; j < size; ++j) {
            if (i != j) {
                Data other = array_get(arr, j);
                if (other > 0 && elem % other == 0) {
                    divisible = true;
                    break;
                }
            }
        }
        if (!divisible) {
            if (!first) {
                cout << " ";
                out << " ";
            }
            cout << elem;
            out << elem;
            first = false;
        }
    }
    cout << endl;
    out << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Error: input file not specified" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "Error opening input file" << endl;
        return 1;
    }

    ofstream output;
    if (argc >= 3) {
        output.open(argv[2]);
    }
    else {
        output.open("output_task2.txt");
    }
    if (!output.is_open()) {
        cout << "Error creating output file" << endl;
        return 1;
    }

    Array* arr = read_array(input);
    if (!arr) {
        cout << "Error: invalid array size/data" << endl;
        output << "Error: invalid array size/data" << endl;
        return 1;
    }

    try {
        process_task2(arr, output);
        array_delete(arr);
        return 0;
    }
    catch (...) {
        array_delete(arr);
        return 1;
    }
}