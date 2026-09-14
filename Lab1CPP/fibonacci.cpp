#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main() {
    ifstream fin("input_fib.txt");
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла\n";
        return 1;
    }
    int n;
    fin >> n;
    Array<long long> arr(n);
    if (n > 0) arr[0] = 0;
    if (n > 1) arr[1] = 1;
    for (int i = 2; i < arr.getSize(); i++)  arr[i] = arr[i - 1] + arr[i - 2];
    for (int i = 0; i < arr.getSize(); i++) cout << arr[i] << " ";
    cout << '\n';
    return 0;
}
