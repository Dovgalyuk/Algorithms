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
    int* mass = new int[size];

    cout << "Enter array value: ";
    for (int i = 0; i < size; i++)
        cin >> mass[i];


    for (int i = 0; i < size; i++)
        if (mass[i] > 10)
        {
            sred_arifmet += mass[i];
            chislo++;
        }

    cout << "Srednearifmeticheskoe " << chislo << " elementov bolshe 10" << sred_arifmet / chislo << endl;
    delete[] mass;
    return 0;
}