#include <iostream>
#include "array.h"

using namespace std;

int main()
{
    int sred_arifmet = 0;
    int chislo = 0;
    int size = 0;
    cout << "Enter array size: ";
    cin >> size;
    Array* arr = array_create(size);
    
    cout << "Enter array value: ";
    for (int i = 0; i < size; i++) {
        int val;
        cin >> val;
        array_set(arr, i, val);
    }
    for (int i = 0; i < size; i++) {
        if (array_get(arr, i) > 10)
        {
            sred_arifmet += array_get(arr, i);
            chislo++;
        }
    }
    cout << "Srednearifmeticheskoe " << chislo << " elementov bolshe 10" << sred_arifmet / chislo << endl;
    array_delete(arr);
    return 0;
}