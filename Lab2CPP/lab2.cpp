#include <iostream>
#include <fstream>

#include "vector.h"
#include "stack.h"

using namespace std;

void merge_sort(Vector *a);
void push_frame(Stack *stack, size_t l, size_t r, int state);
void merge(Vector *a, Vector *tmp, size_t l, size_t m, size_t r);

int main(int argc, char *argv[]) {
    ifstream fin;
    ofstream fout;
    istream *in = &cin;
    ostream *out = &cout;

    if (argc >= 2) {
        fin.open(argv[1]);
        if (!fin) {
            cerr << "Cannot open input file: " << argv[1] << "\n";
            return 1;
        }
        in = &fin;
    }
    if (argc >= 3) {
        fout.open(argv[2], ios::binary);
        if (!fout) {
            cerr << "Cannot open output file: " << argv[2] << "\n";
            return 1;
        }
        out = &fout;
    }

    Vector *v = vector_create();

    Data x;
    while (*in >> x) {
        size_t s = vector_size(v);
        vector_resize(v, s + 1);
        vector_set(v, s, x);
    }

    merge_sort(v);

    for (size_t i = 0; i < vector_size(v); i++) {
        if (i > 0)
            *out << " ";
        *out << vector_get(v, i);
    }
    *out << "\n";

    vector_delete(v);
    return 0;
}

void push_frame(Stack *stack, size_t l, size_t r, int state) {
    stack_push(stack, (Data)l);
    stack_push(stack, (Data)r);
    stack_push(stack, (Data)state);
}

void merge_sort(Vector *a) {
    size_t n = vector_size(a);
    if (n < 2) {
        return;
    }

    Vector *tmp = vector_create();
    vector_resize(tmp, n);

    Stack *stack = stack_create();
    push_frame(stack, 0, n, 0);

    while (!stack_empty(stack)) {
        int state = (int)stack_get(stack);
        stack_pop(stack);
        size_t r = (size_t)stack_get(stack);
        stack_pop(stack);
        size_t l = (size_t)stack_get(stack);
        stack_pop(stack);

        if (r - l < 2)
            continue;

        size_t m = l + (r - l) / 2;

        if (state == 0)
        {
            push_frame(stack, l, r, 1);
            push_frame(stack, m, r, 0);
            push_frame(stack, l, m, 0);
        }
        else
        {
            merge(a, tmp, l, m, r);
        }
    }

    stack_delete(stack);
    vector_delete(tmp);

}

void merge(Vector *a, Vector *tmp, size_t l, size_t m, size_t r) {
    size_t i = l;
    size_t j = m;
    size_t k = l;

    while (i < m && j < r) {
        Data left = vector_get(a, i);
        Data right = vector_get(a, j);
        if (left <= right) {
            vector_set(tmp, k, left);
            i++;
        }
        else {
            vector_set(tmp, k, right);
            j++;
        }
        k++;
    }

    while (i < m) {
        vector_set(tmp, k++, vector_get(a, i++));
    }
    while (j < r) {
        vector_set(tmp, k++, vector_get(a, j++));
    }

    for (size_t t = l; t < r; t++) {
        vector_set(a, t, vector_get(tmp, t));
    }
}