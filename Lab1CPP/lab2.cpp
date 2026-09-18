#include <iostream>
#include <fstream>
#include "array.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    ifstream input2(argv[1]);
    if (!input2.is_open()) {

        return 1;
    }
    size_t size = 0;
    if (!(input2 >> size)) {
        return 1;
    }
    Array* arr = array_create(size);
    int count[1001] = {0};

    for (size_t i = 0; i < size; i++) {
        int val = 0;
        if (!(input2 >> val)) {
            array_delete(arr);
            return 1;
        }

        if (val < 0 or val > 1000) {
            cerr << "Error! Value out of bounds"<<endl;
            array_delete(arr);
            return 1;
        }
        array_set(arr, i, val);
        count[val]++;
    }
    bool f = true;
    for (size_t i = 0; i < array_size(arr); i++) {
        int val = array_get(arr, i);
        if (count[val] == 2) {
            if (!f) cout << " ";
            cout << val;
            f = false;
            count[val] = 0;
        }
    }
    cout << endl;
    array_delete(arr);
    return 0;

}