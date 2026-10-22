#include <iostream>
#include "Array.h"

using namespace std;

int main() {
    Array<int> arr(5);
    cout << "Size: " << arr.getSize() << endl;
    for (size_t i = 0; i < arr.getSize(); i++) {
        arr[i] = (i + 1) * 10;
    }
    cout << "Array: ";

    for (size_t i = 0; i < arr.getSize(); i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
    Array<int> copy = arr;

    copy[0] = 999;

    cout << "Original: " << arr[0] << endl;
    cout << "Copy: " << copy[0] << endl;
    arr = arr;

    cout << "Self-assignment: ";

    for (size_t i = 0; i < arr.getSize(); i++) {
        cout << arr[i] << " ";
    }

    cout << endl;
    try {
        cout << arr[5] << endl;
    }
    catch (const out_of_range& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}