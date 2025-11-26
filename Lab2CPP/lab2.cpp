#include <iostream>
#include <fstream>
#include "vector.h"
#include "stack.h"

using namespace std;

void merge(Vector* v, size_t left, size_t mid, size_t right, Vector* temp) {
    size_t i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (vector_get(v, i) <= vector_get(v, j)) {
            vector_set(temp, k++, vector_get(v, i++));
        }
        else {
            vector_set(temp, k++, vector_get(v, j++));
        }
    }
    while (i < mid) vector_set(temp, k++, vector_get(v, i++));
    while (j < right) vector_set(temp, k++, vector_get(v, j++));
    for (size_t t = left; t < right; ++t)
        vector_set(v, t, vector_get(temp, t));
}

void merge_sort(Vector* v) {
    size_t n = vector_size(v);
    Vector* temp = vector_create();
    vector_resize(temp, n);

    for (size_t width = 1; width < n; width *= 2) {
        for (size_t left = 0; left < n; left += 2 * width) {
            size_t mid = min(left + width, n);
            size_t right = min(left + 2 * width, n);
            merge(v, left, mid, right, temp);
        }
    }
    vector_delete(temp);
}

void solve_file(const char* filename) {
    Vector* v = vector_create();

    ifstream file(filename);
    
    int x;
    while (file >> x) {
        size_t sz = vector_size(v);
        vector_resize(v, sz + 1);
        vector_set(v, sz, x);
    }

    merge_sort(v);

    for (size_t i = 0; i < vector_size(v); ++i)
        cout << vector_get(v, i) << " ";
    cout << endl;
    vector_delete(v);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            solve_file(argv[i]);
        }
    }
    else {
        const char* filenames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt" };
        for (int i = 0; i < 5; i++) {
            solve_file(filenames[i]);
        }
    }
    return 0;
}
