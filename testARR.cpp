// "Проверить работу соответствующей тестовой программы (программой)"
// не совсем понял, как именно я должен это сделать, поэтому решил сделать файл, который проверяет дин. массив
// (ну и я решил вынести реализацию массива в отдельный файл)
// (в итоге сделал подпроект)
//(skill issue)
#include "array.h"
#include <iostream>
#include <fstream>

using namespace std;

int test() {
    ifstream input("input.txt");
    if (!input.is_open()) {
        cerr << "Cannot open input.txt" << endl;
        return 1;
    }

    size_t n;
    input >> n;

    ::array<int> arr(n); // :: - потому что я сделал свой пользовательский класс таким же именем, как и обычный и мне стало лень переписывать это всё

    for (size_t i = 0; i < n; ++i) {
        input >> arr[i];
    }

    cout << "Size of array: " << arr.size() << endl;

    cout << "Array contents: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
  }