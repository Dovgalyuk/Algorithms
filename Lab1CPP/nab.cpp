#include <iostream>
#include <fstream>
#include "Array.h"
using namespace std;
int main(int argc, char* argv[] ) {
    setlocale(LC_ALL, "Russian");
    if (argc < 2) {
        cout<<"Input file not specified" << endl;
        return 1;
    }
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }
    size_t n;
    input >> n;
    Array<int> nab(n);
    for (size_t i = 0; i < n; i++) {
        input>>nab[i];
    }
    int lista[1001] = {};
    for (size_t i = 0 ; i< n ; i++) {
        lista[nab[i]]++;
    }
    int bes = 0 , count = 0 ;
    for (int i = 0 ; i < 1001 ; i++) {
        if (lista[i] > count ) {
            count = lista[i];
            bes = i;
        }
    }
    cout << "Самое частое число: " << bes << " (встречается "<< count << " раз)"<< endl;
}