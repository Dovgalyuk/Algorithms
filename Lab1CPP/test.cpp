#include <iostream>
#include "array.h"

using namespace std;

// Проверить работу соответствующей тестовой программы

int main() {
    Array<int> arr(5);
    for (int i = 0; i < arr.getSize(); i++) arr[i] = i * 10;
    for (int i = 0; i < arr.getSize(); i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}
