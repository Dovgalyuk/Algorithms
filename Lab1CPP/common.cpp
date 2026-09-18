#include "common.h"

void print_array(ostream &out, Array *arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++) {
        if (i > 0) out << " ";
        out << array_get(arr, i);
    }
    out << endl;
}

Array *array_create_and_read(ifstream &input) {
    int n;
    input >> n;

    if (n <= 0) {
        return nullptr;
    }

    Array *arr = array_create(n);

    for (int i = 0; i < n; ++i) {
        int x;
        input >> x;
        array_set(arr, i, x);
    }

    return arr;
}

void print_error(const char* message, ofstream &output) {
    cout << message << endl;
    output << message << endl;
}
