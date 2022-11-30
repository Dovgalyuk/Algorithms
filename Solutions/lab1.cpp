//
// Created by Artem Raykh on 14.11.2022.
//

#include <iostream>
#include "array.h"
#include <ctime>
#include "stdlib.h"

using std::cout;
using std::cin;
using std::endl;

void shiftArray(Array<int> *array, bool toLeft) {
    if (toLeft) {
        array->set(0, 0);
        for (int i = 0; i < array->size(); i++) {
            array->set(i, array->get(i+1));
        }
    } else {
        array->set(array->size() - 1, 0);
        for (int i = array->size() - 1; i >= 0; i--) {
            array->set(i, array->get(i - 1));
        }
    }
}

void solution() {

    srand(time(NULL));

    while (true) {
        int size, shift, direction;
        cout << "Input size: " << endl;
        cin >> size;
        cout << "Choose shift count an direction (0 <- direction left, 1 -> direction right, 9 - exit): " << endl;
        cin >> shift >> direction;

        if (direction == 9) {
            break;
        }

        if (direction != 0 && direction != 1) {
            cout << "Wrong direction input" << endl;
        }

        Array<int>* firstArray = new Array<int>(size);

        // Теперь компилируется :)
        Array<int>* secondArray = new Array<int>(firstArray);

        Array<int>* array = secondArray;

        for (size_t i = 0; i < size; ++i) {
            array->set(i, rand());
        }

        cout << "Non shifted array: " << endl;
        cout << array << endl;

        for (int i = 0; i < shift; i++) {
            if (direction == 0) {
                shiftArray(array, true);
            } else {
                shiftArray(array, false);
            }
        }

        cout << "Shifted array: " << endl;
        cout << array << endl;

        delete array;
    }
};

int main() {
    solution();
}