#include <iostream>
#include <fstream>
#include <string>
#include "array.h"

using namespace std;

static void find_greater_than_sum(const Array& arr) {
    long long total = 0;
    for (size_t i = 0; i < arr.size(); i++)
        total += arr.get(i);

    cout << "Indices of elements greater than total sum (" << total << "): ";

    bool first = true;
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr.get(i) > total) {
            if (!first) cout << ' ';
            cout << i;
            first = false;
        }
    }
    if (first) cout << "None ";
}

static void print_unique_elements(const Array& arr) {
    cout << "Unique elements: ";

    bool printed_any = false;
    for (size_t i = 0; i < arr.size(); i++) {
        int x = arr.get(i);
        int cnt = 0;
        for (size_t j = 0; j < arr.size(); j++)
            if (arr.get(j) == x) ++cnt;

        if (cnt == 1) {
            if (printed_any) cout << ' ';
            cout << x;
            printed_any = true;
        }
    }
    if (!printed_any) cout << "None";
}

static Array read_array_from_file(const string& path) {
    ifstream in(path);
    if (!in) {
        cerr << "Cannot open input file: " << path << '\n';
        exit(1);
    }

    size_t n = 0;
    in >> n;
    if (n == 0) {
        cerr << "Invalid array size\n";
        exit(1);
    }

    Array arr(n);
    for (size_t i = 0; i < n; i++) {
        int v; in >> v;
        arr.set(i, v);
    }
    return arr;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: Lab1CPP <input_file>\n";
        return 1;
    }

    Array arr = read_array_from_file(argv[1]);
    find_greater_than_sum(arr);
    print_unique_elements(arr);
    return 0;
}
