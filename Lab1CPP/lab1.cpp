#include <iostream>
#include <fstream>
#include "array.h"
using namespace std;

int sumdigits(int n) {
    size_t sum = 0;
    if (n < 0 ) {
        n = -n;
    }
    while (n > 0) {
        sum += n % 10;
        n /=10;
    }
    return sum;
}

int main( int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    ifstream input(argv[1]);

    if (!input.is_open()) {
        return 1;
    }
    size_t size = 0;
    if (!(input >> size)) {
        return 1;
    }
    
    Array*arr = array_create(size);
    for (size_t i = 0; i < size; i++) {
        Data val;
        input >> val;
        array_set(arr, i, val);
    }
    size_t sum = 0;
    for (size_t i = 0; i < array_size(arr); i++) {
        sum += sumdigits(array_get(arr, i));
    }
    cout << sum << endl;
    array_delete(arr);
    return 0;
}