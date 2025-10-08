#include "array.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

size_t longest_odd_sequence(const Array* arr) {
    size_t max_len = 0;
    size_t current_len = 0;

    for (size_t i = 0; i < array_size(arr); ++i) {
        if (array_get(arr, i) % 2 != 0) {
            current_len++;
            if (current_len > max_len) max_len = current_len;
        }
        else {
            current_len = 0;
        }
    }

    return max_len;
}

void shift_array(Array* arr, int steps, bool left) {
    size_t n = array_size(arr);
    if (steps >= static_cast<int>(n)) {
        for (size_t i = 0; i < n; ++i) array_set(arr, i, 0);
        return;
    }

    if (left) {
        for (size_t i = 0; i < n - steps; ++i) {
            array_set(arr, i, array_get(arr, i + steps));
        }
        for (size_t i = n - steps; i < n; ++i) {
            array_set(arr, i, 0);
        }
    }
    else { //vpravo
        for (size_t i = n - 1; i >= static_cast<size_t>(steps); --i) {
            array_set(arr, i, array_get(arr, i - steps));
        }
        for (int i = 0; i < steps; ++i) {
            array_set(arr, i, 0);
        }
    }
}

int main(int argc, char* argv[])
{
    string input_filename = (argc > 1) ? argv[1] : "input.txt";
    ifstream input(input_filename);
    if (!input.is_open()) {
        cerr << "Cannot open " << input_filename << endl;
        return 1;
    }

    size_t n;
    input >> n;

    Array* arr = array_create(n);

    for (size_t i = 0; i < n; ++i) {
        int sdvig;
        input >> sdvig;
        array_set(arr, i, sdvig);
    }

    int steps;
    input >> steps;

    string napravlenie;
    input >> napravlenie;
    bool left = (napravlenie == "left");

    ofstream output("output.txt");
    if (!output.is_open()) {
        cerr << "Cannot create output.txt" << endl;
        array_delete(arr);
        return 1;
    }

    size_t max_len = longest_odd_sequence(arr);
    cout << "Max odd sequence length: " << max_len << endl;
    output << max_len << endl;

    Array* shifted_arr = array_create(n);
    for (size_t i = 0; i < n; ++i) {
        array_set(shifted_arr, i, array_get(arr, i));
    }
    shift_array(shifted_arr, steps, left);
    cout << "Array after " << napravlenie << " shift by " << steps << ": ";
    for (size_t i = 0; i < array_size(shifted_arr); ++i) {
        cout << array_get(shifted_arr, i) << " ";
        output << array_get(shifted_arr, i) << " ";
    }
    cout << endl;

    output << endl;

    array_delete(arr);
    array_delete(shifted_arr);

    return 0;
}