#include <iostream>
#include "array.h"
#include <ctime>
#include "stdlib.h"

typedef Array<int> MyArray;

using std::cout;
using std::cin;
using std::endl;

void solution();

int main()
{
    MyArray *arr = new MyArray(10);

    if (arr->size() != 10)
    {
        std::cout << "Invalid array size\n";
        return 1;
    }

    for (int i = 0 ; i < 10 ; ++i)
        arr->set(i, i * 2);

    for (int i = 0 ; i < 10 ; ++i)
    {
        if (arr->get(i) != i * 2)
        {
            std::cout << "Invalid array element " << i << "\n";
            return 1;
        }
    }

    delete arr;

    solution();
}

void solution() {
    srand(time(NULL));
    int size, shift, direction;
    cout << "Input size: " << endl;
    cin >> size;
    cout << "Choose shift count an direction (0 -> direction left, 1 -> direction right): " << endl;
    cin >> shift >> direction;
    if (direction != 0 && direction != 1) {
        cout << "Wrong direction input" << endl;
    }

    Array<int>* array = new Array<int>(size);

    for (size_t i = 0; i < size; ++i) {
        array->set(i, rand());
    }

    cout << "Non shifted array: " << endl;
    cout << array << endl;

    if (direction == 0) {
        cout << "Shifting to left: " << endl;
        for (int i = 0; i < array->size(); i++) {
            if (i + shift < array->size())
                array->set(i, array->get(i+shift));
            else
                array->set(i, 0);
            cout << array << endl;
        }
    } else if (direction == 1) {
        cout << "Shifting to right: " << endl;
        for (int i = array->size() - 1; i >= 0; i--) {
            if (i - shift < array->size())
                array->set(i, array->get(i-shift));
            else
                array->set(i, 0);
            cout << array << endl;
        }
    }

    cout << "Shifted array: " << endl;
    cout << array << endl;

    delete array;
}
