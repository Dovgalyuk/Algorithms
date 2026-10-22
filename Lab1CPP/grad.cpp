#include <fstream>
#include <iostream>
#include "Array.h"

using namespace std;
int main(int argc, char* argv[]) {
    setlocale(LC_ALL ,"RU");
    if (argc < 2) {
        cout << "Input file not specified" << endl;
        return 1;
    }
    ifstream input(argv[1]);

    if (!input.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }
    size_t n;
    input>>n;
    Array<int> grades(n);
    int count5  = 0 , count4 = 0 , count3 = 0 , count2 = 0;

    for (size_t i = 0; i < n; i++) {
        input >> grades[i];
        if (grades[i] == 5) {
            count5++;
        }
        else if (grades[i] == 4) {
            count4++;
        }
        else if (grades[i] == 3) {
            count3++;
        }
        else{
            count2++;
        }
    }
    cout << count5 << " " << count4 << " " << count3 << " " << count2 << endl;
}