#include "array.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    ifstream input(argv[1]);
    int size;
    if (!(input >> size) || (size != 365 && size != 366))
        return 1;

    Array *rainfall = array_create(size);
    for (int i = 0; i < size; i++)
    {
        int value;
        if (!(input >> value))
        {
            array_delete(rainfall);
            return 1;
        }
        array_set(rainfall, i, value);
    }

    int days_in_month[12] = {31, 28, 31, 30, 31, 30,
                             31, 31, 30, 31, 30, 31};
    if (size == 366)
        days_in_month[1] = 29;

    int day = 0;
    for (int month = 0; month < 12; month++)
    {
        long long sum = 0;
        for (int i = 0; i < days_in_month[month]; i++)
            sum += array_get(rainfall, day++);

        if (month > 0)
            cout << ' ';
        cout << sum;
    }
    cout << '\n';

    array_delete(rainfall);
    return 0;
}
