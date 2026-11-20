#include "common.h"

Array* array_create_and_read(std::ifstream& inFile) {
    int n;
    if (!(inFile >> n) || n < 0) {
        return nullptr;
    }

    Array* arr = new Array(n);
    for (int i = 0; i < n; ++i) {
        int x;
        if (!(inFile >> x)) {
            delete arr;
            return nullptr;
        }
        arr->set(i, x);
    }

    return arr;
}