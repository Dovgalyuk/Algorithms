#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "../LibraryCPPClass/array.h"

using namespace std;

Array readArrayFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка при чтении файла" << endl;
        return Array(0);
    }

    size_t n;
    file >> n;

    Array arr(n);
    for (size_t i = 0; i < n; ++i) {
        Data val;
        if (!(file >> val)) {
            std::cerr << "Ошибка: недостаточно элементов" << std::endl;
            return Array(0);
        }
        arr.set(i, val);
    }

    file.close();

    return arr;
}

void reverseArray(const string& filename) {
    Array arr = readArrayFromFile(filename);
    if (arr.size() == 0) {
        return;
    }

    size_t n = arr.size();
    for (size_t i = 0; i < n / 2; i++) {
        Data temp = arr.get(i);
        arr.set(i, arr.get(n - 1 - i));
        arr.set(n - 1 - i, temp);
    }

    arr.print();
}

void shiftArray(const string& filename, char direction, size_t steps) {
    Array arr = readArrayFromFile(filename);
    if (arr.size() == 0) {
        return;
    }

    size_t n = arr.size();
    steps = steps % n;

    if (direction == 'l') {
        for (size_t i = 0; i < n - steps; ++i) {
            arr.set(i, arr.get(i + steps));
        }
        for (size_t i = n - steps; i < n; ++i) {
            arr.set(i, 0);
        }
    }
    else if (direction == 'r') {
        for (size_t i = n - 1; i >= steps; --i) {
            arr.set(i, arr.get(i - steps));
        }
        for (size_t i = 0; i < steps; ++i) {
            arr.set(i, 0);
        }
    }
    else {
        cerr << "Неправильное направление: используйте 'l' или 'r'" << endl;
        return;
    }

    arr.print();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Использование: " << argv[0] << " <reverse|shift> <filename> [direction steps]" << endl;
        return 1;
    }

    string mode = argv[1];
    if (mode == "reverse") {
        reverseArray(argv[2]);
    }
    else if (mode == "shift") {
        shiftArray(argv[2], argv[3][0], stoul(argv[4]));
    }
    else {
        return 1;
    }

    return 0;
}