#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "array.h"

using namespace std;

void countArrayElements(const Array& arr) {
    int positive = 0, negative = 0, zero = 0;
    
    for (size_t i = 0; i < arr.size(); i++) {
        Data num = arr.get(i);
        if (num > 0) {
            positive++;
        } else if (num < 0) {
            negative++;
        } else {
            zero++;
        }
    }
    
    cout << "Положительных: " << positive << endl;
    cout << "Отрицательных: " << negative << endl;
    cout << "Нулевых: " << zero << endl;
}

void findElementsAppearingTwice(const Array& arr) {
    map<Data, int> frequency;
    
    for (size_t i = 0; i < arr.size(); i++) {
        Data num = arr.get(i);
        frequency[num]++;
    }
    
    cout << "Элементы, встречающиеся ровно два раза: ";
    bool found = false;
    
    for (const auto& pair : frequency) {
        if (pair.second == 2) {
            cout << pair.first << " ";
            found = true;
        }
    }
    
    if (!found) {
        cout << "таких элементов нет";
    }
    cout << endl;
}

Array readArrayFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return Array(0);
    }
    
    size_t size;
    file >> size;
    
    Array arr(size);
    for (size_t i = 0; i < size; i++) {
        Data value;
        file >> value;
        arr.set(i, value);
    }
    
    file.close();
    return arr;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    string filename = argv[1];
    
    Array arr = readArrayFromFile(filename);
    if (arr.size() == 0) {
        return 1;
    }
    
    cout << "Размер массива: " << arr.size() << endl;
    cout << "Элементы массива: ";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr.get(i) << " ";
    }
    cout << endl << endl;
    
    cout << "=== Результат первой функции ===" << endl;
    countArrayElements(arr);
    cout << endl;
    
    cout << "=== Результат второй функции ===" << endl;
    findElementsAppearingTwice(arr);
    
    return 0;
}