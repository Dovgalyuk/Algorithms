#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main(int argc, char* argv[]) {
    string filename = (argc > 1) ? argv[1] : "input_fib1.txt";
    ifstream fin(filename);
    if (!fin.is_open()) return 1;
    int n;
    fin >> n;
    Array arr(n);
    if (n > 0) arr.set(0, 0);
    if (n > 1) arr.set(1, 1);
    for (size_t i = 2; i < arr.size(); i++)
        arr.set(i, arr.get(i - 1) + arr.get(i - 2));
    for (size_t i = 0; i < arr.size(); i++)
        cout << arr.get(i) << " ";
    cout << endl;
    return 0;
}
