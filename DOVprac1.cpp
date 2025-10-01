#include "test.h"
#include "array.h"
#include <iostream>
#include <fstream>

using namespace std;
size_t longest_odd_sequence(const ::array<int>& arr) {
    size_t max_len = 0;
    size_t current_len = 0;

    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] % 2 != 0) {
            current_len++;
            if (current_len > max_len) max_len = current_len;
        }
        else {
            current_len = 0;
        }
    }

    return max_len;
}



void shift_array(::array<int>& arr, int steps, bool left) {
    size_t n = arr.size();
    if (steps >= static_cast<int>(n)) {
        for (size_t i = 0; i < n; ++i) arr[i] = 0;
        return;
    }

    if (left) {
        for (size_t i = 0; i < n - steps; ++i) {
            arr[i] = arr[i + steps];
        }
        for (int i = n - steps; i < static_cast<int>(n); ++i) {
            arr[i] = 0;
        }
    }
    else { //vpravo
        for (int i = n - 1; i >= steps; --i) {
            arr[i] = arr[i - steps];
        }
        for (int i = 0; i < steps; ++i) {
            arr[i] = 0;
        }
    }
}


int main() 
{
    ifstream input("input.txt");
    if (!input.is_open()) {
        cerr << "Cannot open input.txt" << endl;
        return 1;
    }

    size_t n;
    input >> n;

    ::array<int> arr(n);

    for (size_t i = 0; i < n; ++i) {
        input >> arr[i];
    }

    ofstream output("output.txt");
    if (!output.is_open()) {
        cerr << "Cannot create output.txt" << endl;
        return 1;
    }
    output << "Size of array: " << arr.size() << endl;

    output << "Array contents: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        output << arr[i] << " ";
        if (i + 1 == arr.size()) {
            output << endl;
        }
    }
    

    size_t max_len = longest_odd_sequence(arr);
    cout << "Max odd sequence length: " << max_len << endl;
    output << "Max odd sequence length: " << max_len << endl;

    ::array<int> shifted_arr(n);
    for (size_t i = 0; i < n; ++i) {
        shifted_arr[i] = arr[i];
    }
    shift_array(shifted_arr, 2, false);
    cout << "Array after right shift by 2: ";
    output << "Array after right shift by 2: ";
    for (size_t i = 0; i < shifted_arr.size(); ++i) {
        cout << shifted_arr[i] << " ";
        output << shifted_arr[i] << " ";
    }
    cout << endl;

    output << endl;

    return 0;
}
