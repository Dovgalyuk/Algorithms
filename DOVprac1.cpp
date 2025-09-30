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





int main() {
    test();
    ifstream input("input.txt");
    size_t n;
    input >> n;

    ::array<int> arr(n);
    for (size_t i = 0; i < n; ++i) {
        input >> arr[i];
    }

    //4
    cout << "Max odd sequence length: " << longest_odd_sequence(arr) << endl;

    //5
    shift_array(arr, 2, false); //vpravo

    cout << "Array after right shift by 2: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
