#include <iostream>
#include <fstream>
#include "array.h"
using namespace std;

void Schet(const Array &arr) {
    Array counts(1001);
    for (size_t i = 0;i < 1001;i++) {
        counts.set(i,0);
    }
    for (size_t i = 0;i<arr.size();++i) {
        int num = arr.get(i);
        int count = counts.get(num);
        counts.set(num, count + 1);
    }
    cout << "Числа которые встречаются один раз: ";
    for (size_t i = 0;i < arr.size();++i) {
        int num = arr.get(i);
        if (counts.get(num) == 1) {
            cout << num << " ";
        }
    }
}
int main(int argc, char* argv[]) {
    string filename = "text2_1.txt";
    if (argc >= 2) {
        filename = argv[1];
    }
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "файл не прочитан";
        return 1;
    }
    size_t size = 0;
    file >> size;
    Array arr(size);
    for (size_t i = 0;i < size;++i) {
        int num = 0;
        file >> num;
        arr.set(i,num);
    }
    file.close();
    Schet(arr);
    return 0;
}
