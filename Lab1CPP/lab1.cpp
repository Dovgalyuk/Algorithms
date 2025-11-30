#include <iostream>
#include <fstream>
#include  "task1.h"
#include  "task2.h"
#include  "array.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cerr << "Add an argument" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error: Could not open file" << endl;
        return 1;
    }

    int n;
    file >> n;
    Array* arr = array_create(n);

    for (int i = 0; i < n; i++) {
        int x;
        file >> x;
        array_set(arr, i, x);
    }

    int a, b;
    file >> a >> b;

    cout << "Array size " << n << endl;
    cout << "Array elements ";
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    cout << "Interval " << a << " " << b << endl;

    size_t maxLen = task1(arr);
    cout << "The maximum length of a segment of odd numbers: " << maxLen << endl;

    task2(arr, a, b);

    cout << "Compressed array: ";
    for (int i = 0; i < n; i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    array_delete(arr);
    file.close();
    return 0;
}
