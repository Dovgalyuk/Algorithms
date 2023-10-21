#include <iostream>
#include <vector>
#include "Array.h"
using namespace std;
void summapos(const Array& arr) {
    cout << "Massiv:";
    for (int k = 0; k < arr.size(); k++) {
        cout << arr.get(k) << " ";
    }
    cout << endl;

    int sum = 0;
    for (int k = 0; k < arr.size(); k++) {
        if (arr.get(k) > 0 && arr.get(k) % 2 == 0) {
            sum += arr.get(k);
        }
    }

    cout << "Summaa (1 zadanie):" << sum << endl;
}

void nedel(const Array& arr) {
    cout << "Massiv:" << " ";
    for (int k = 0; k < arr.size(); k++) {
        cout << arr.get(k) << " ";
    }
    cout << endl;
    cout << "nedel:" << " ";
    for (int i = 0; i < arr.size(); ++i) {
        bool digit = false;
        for (int j = 0; j < arr.size(); ++j) {
            if (arr.get(i) % arr.get(j) == 0 && i != j) {
                digit = true;
                break;
            }
        }
        if (!digit) {
            cout << arr.get(i) << " ";
        }
    }
}

int main() {
    cout << "Input array: ";
    int size;
    cin >> size;
    Array mas(size);
    srand(time(0));
    for (int i = 0; i < size; i++) {
        mas.set(i, rand() % 100);
    }
    cout << std::endl;
    summapos(mas);
    nedel(mas);
    return 0;
}