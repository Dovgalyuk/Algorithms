#include <iostream>
#include "vector.h"

using namespace std;

typedef Vector<int> MyVector;

int main()
{
    MyVector vector;
    
    vector.resize(5);

    if (vector.size() != 5) {
        cout << "Incorrect resize\n";
        return 1;
    }

    for (size_t i = 0; i < vector.size(); i++) {
        vector.set(i, static_cast<int>(i));
    }

    for (size_t i = 0; i < vector.size(); i++) {
        if (vector.get(i) != (int)i) {
            cout << "Incorrect vector elemt\n";
            return 1;
        }
    }

    vector.set(3, 15);
    if (vector.get(3) != 15) {
        cout << "Incorrect vector elemt\n";
        return 1;
    }

    vector.resize(10);
    if (vector.size() != 10) {
        cout << "Incorrect resize\n";
        return 1;
    }

    for (size_t i = 0; i < vector.size(); i++) {
        cout << vector.get(i)<<" ";
    }
    cout << "\n";

    vector.resize(2);
    if (vector.size() != 2) {
        cout << "Incorrect resize\n";
        return 1;
    }

    for (size_t i = 0; i < vector.size(); i++) {
        if (vector.get(i) != (int)i) {
            cout << "Incorrect vector elemt\n";
            return 1;
        }
    }

    //Проверка на правильное изменение размера
    for (size_t i = 0; i < 1000000; i++) {
        vector.resize(i);
    }

}