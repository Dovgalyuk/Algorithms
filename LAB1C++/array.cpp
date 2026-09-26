#include <iostream>
using namespace std;

int main() {
    const int n = 5;
    const int copyi[n] = {4, 7, 2, 9, 1};
    int* arr = new int[n]{4, 7, 2, 9, 1};
    if (arr == nullptr) {
        cerr << "Memory allocation failed\n";
        return 1;
    }
    cout << "Memory allocated\n";

    bool readCorrect= true;
    for (int i = 0; i < n; ++i) {
        if (arr[i] != copyi[i]) {
            readCorrect = false;
            break;
        }
    }
    cout << (readCorrect ? "Reading successful\n" : "Reading error\n");

    delete[] arr;
    arr = nullptr;
    cout << (arr == nullptr ? "Memory released\n" : "Memory release error\n");
}