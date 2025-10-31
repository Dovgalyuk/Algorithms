#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
#include "array.h"

using namespace std;

long long factorial(int n) {
    if (n < 0) return 0;
    long long f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}

void task4(Array& prarr) {
    for (size_t i = 0; i < prarr.size(); i++) {
        Data val = prarr.get(i);
        prarr.set(i, factorial(val));
        cout << prarr.get(i) << " ";
    }
    cout << endl;
}

void task5(Array& prarr, Data a, Data b) {
    size_t write_index = 0;
    size_t asize = prarr.size();

    for (size_t i = 0; i < asize; i++) {
        Data current = prarr.get(i);
        if (current < a || current > b) {
            prarr.set(write_index, current);
            write_index++;
        }
    }

    for (size_t i = write_index; i < asize; i++) {
        prarr.set(i, 0);
    }

    for (size_t i = 0; i < asize; i++) {
        cout << prarr.get(i);
        if (i < asize - 1) cout << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 1;
    }

    ifstream in(argv[1]);
    if (!in.is_open()) {
        return 1;
    }

    size_t size4;
    in >> size4;

    if (size4 > 0) {
        Array arr4(size4);

        for (size_t i = 0; i < size4; i++) {
            Data value;
            in >> value;
            arr4.set(i, value);
        }

        task4(arr4);
    }

    size_t size5;
    in >> size5;

    if (size5 > 0) {
        Array arr5(size5);

        for (size_t i = 0; i < size5; i++) {
            Data value;
            in >> value;
            arr5.set(i, value);
        }

        Data a, b;
        in >> a >> b;

        task5(arr5, a, b);
    }

    in.close();
    return 0;
}