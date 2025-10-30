#include <iostream>
#include <fstream>
#include <map>
#include "array.h"

using namespace std;

void mostFrequent(const Array &arr) {
    map<Data, int> freq;
    for (size_t i = 0; i < arr.size(); ++i)
        freq[arr.get(i)]++;

    Data most = arr.get(0);
    int maxCount = 0;
    for (auto &p : freq) {
        if (p.second > maxCount) {
            maxCount = p.second;
            most = p.first;
        }
    }

    cout << "Самое частое число: " << most<< "(встречается " << maxCount << " раз)";
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
        fin >> val;
        arr.set(i, val);
    }

    mostFrequent(arr);

    return 0;
}