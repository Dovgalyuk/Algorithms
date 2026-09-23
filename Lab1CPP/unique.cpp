#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main(int argc, char* argv[]) {
    string filename = (argc > 1) ? argv[1] : "input_unique1.txt";
    ifstream fin(filename);
    if (!fin.is_open()) return 1;
    int n;
    fin >> n;
    Array arr(n);
    for (size_t i = 0; i < arr.size(); i++) {
        int val;
        fin >> val;
        arr.set(i, val);
    }
    int freq[1001] = {0};
    for (size_t i = 0; i < arr.size(); i++) {
        int x = arr.get(i);
        if (x >= 0 && x <= 1000) freq[x]++;
    }
    bool found = false;
    for (size_t i = 0; i < arr.size(); i++) {
        int x = arr.get(i);
        if (x >= 0 && x <= 1000 && freq[x] == 1) {
            cout << x << " ";
            found = true;
        }
    }
    if (!found) cout << "No unique elements";
    cout << endl;

    return 0;
}
