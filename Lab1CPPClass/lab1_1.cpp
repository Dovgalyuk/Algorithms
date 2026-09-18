#include <iostream>
#include <fstream>
#include "array.h"
using namespace std;
void Find_Two_Min(const Array &arr) {
    int min = arr.get(0);
    int min2 = arr.get(1);
    if (min < min2) {
        min = arr.get(0);
        min2 = arr.get(1);
    }
    else {
        min = arr.get(1);
        min2 = arr.get(0);
    }
    for (size_t i = 2;i < arr.size();++i) {
        if (arr.get(i) < min) {
            min2 = min;
            min = arr.get(i);
        }
        else if (arr.get(i) < min2) {
            min2 = arr.get(i);
        }
    }
    cout << "Min: " << min << "\n" << "Min_two: " << min2;
}
int main(int argc, char* argv[]) {
    string filename = "text1_1.txt";
    if (argc >= 2) {
        filename = argv[1];
    }
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "файл не найден";
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
    Find_Two_Min(arr);
    return 0;
}
