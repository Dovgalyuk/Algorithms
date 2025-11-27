#include <iostream>
#include <fstream>
#include "vector.h"
#include "stack.h"

using namespace std;

void merge(Vector* v, size_t left, size_t mid, size_t right, Vector* temp) {
    size_t i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (vector_get(v, i) <= vector_get(v, j))
            vector_set(temp, k++, vector_get(v, i++));
        else
            vector_set(temp, k++, vector_get(v, j++));
    }
    while (i < mid) vector_set(temp, k++, vector_get(v, i++));
    while (j < right) vector_set(temp, k++, vector_get(v, j++));
    for (size_t t = left; t < right; ++t)
        vector_set(v, t, vector_get(temp, t));
}

void merge_sort(Vector* v) {
    size_t n = vector_size(v);
    if (n <= 1) return;

    Vector* temp = vector_create();
    vector_resize(temp, n);

    Stack* st = stack_create();

    constexpr size_t MAXN = 200000;

    stack_push(st, (Data)(0 * MAXN + n));  
    stack_push(st, (Data)(0 * 10 + 0)); 

    while (!stack_empty(st)) {

        int packed_info = stack_get(st);
        stack_pop(st);

        int packed_range = stack_get(st);
        stack_pop(st);

        size_t left = packed_range / MAXN;
        size_t right = packed_range % MAXN;

        size_t mid = packed_info / 10;
        int stage = packed_info % 10;

        if (stage == 0) {
            if (right - left <= 1)
                continue;

            mid = left + (right - left) / 2;

            stack_push(st, (Data)(left * MAXN + right));
            stack_push(st, (Data)(mid * 10 + 1));

            stack_push(st, (Data)(mid * MAXN + right));
            stack_push(st, (Data)(0 * 10 + 0));

            stack_push(st, (Data)(left * MAXN + mid));
            stack_push(st, (Data)(0 * 10 + 0));
        }
        else {
            merge(v, left, mid, right, temp);
        }
    }

    stack_delete(st);
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
        for (int i = 1; i < argc; i++)
            solve_file(argv[i]);
    }
    else {
        const char* filenames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt", "input_big.txt" };
        for (int i = 0; i < 6; i++)
            solve_file(filenames[i]);
    }
    return 0;
}
