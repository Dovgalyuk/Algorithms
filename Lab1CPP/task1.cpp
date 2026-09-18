#include "apfel.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

static unsigned long long factorial(Data n) {
    if (n < 0) {
        throw std::invalid_argument("Negative value for factorial");
    }
    if (n > 20) {
        throw std::out_of_range("Factorial value causes integer overflow");
    }
    unsigned long long res = 1;
    for (Data i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

static void process_task1(Array* arr, ostream& out) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; ++i) {
        Data val = array_get(arr, i);
        unsigned long long fact = factorial(val);
        string sep = (i + 1 == size ? "" : " ");
        cout << fact << sep;
        out << fact << sep;
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
        output.open("output_task1.txt");
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
        process_task1(arr, output);
        array_delete(arr);
        return 0;
    }
    catch (...) {
        array_delete(arr);
        return 1;
    }
}