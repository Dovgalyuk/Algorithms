#include <iostream>
#include <fstream>
#include <map>
#include "array.h"

using namespace std;

void rainfallStats(const Array &arr) {
    if (arr.size() < 28) {
        cout << "Ошибка: в месяце не может быть меньше 28 дней" << endl;
        return;
    }
    double sum1 = 0, sum2 = 0, sum3 = 0;
    for (size_t i = 0; i < 10; ++i) sum1 += arr.get(i);
    for (size_t i = 10; i < 20; ++i) sum2 += arr.get(i);
    for (size_t i = 20; i < arr.size(); ++i) sum3 += arr.get(i);

    cout << "Средние осадки (мм):" << endl;
    cout << "1-я декада: " << sum1 / 10 << endl;
    cout << "2-я декада: " << sum2 / 10 << endl;
    cout << "3-я декада: " << sum3 / (arr.size() - 20);
}

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        std::cerr << "Не хватает аргументов командной строки!" << std::endl;
        return 1;
    }

    ifstream fin(argv[1]);

    size_t n;
    fin >> n;

    Array arr(n);
    for (size_t i = 0; i < n; ++i) {
        Data val;
        fin>>val;
        arr.set(i, val);
    }

    rainfallStats(arr);

    return 0;
}