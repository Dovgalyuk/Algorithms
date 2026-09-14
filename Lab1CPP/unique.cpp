#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main() {
    ifstream fin("input_unique.txt");
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла\n";
        return 1;
    }
    int n;
    fin >> n;
    Array<int> arr(n);
    for (int i = 0; i < n; i++) fin >> arr[i];
    int freq[1001] = {0};
    for (int i = 0; i < arr.getSize(); i++) {
        int x = arr[i];
        if (x >= 0 && x <= 1000)  freq[x]++;
    }
    bool found = false;
    for (int i = 0; i < arr.getSize(); i++) {
        int x = arr[i];
        if (x >= 0 && x <= 1000 && freq[x] == 1) {
            cout << x << " ";
            found = true;
        }
    }
    if (!found) cout << "Нет уникальных";
    cout << '\n';
    return 0;
}
