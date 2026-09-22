#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }


    ifstream file(argv[1]);

    if (!file)
    {
        return 1;
    }


    int n;
    file >> n;


    Array<int> speed(n);


    for (int i = 0; i < n; i++)
    {
        int value;
        file >> value;
        speed.set(i, value);
    }


    int maxSpeed = speed.get(0);


    for (int i = 1; i < n; i++)
    {
        if (speed.get(i) > maxSpeed)
        {
            maxSpeed = speed.get(i);
        }
    }


    int first = -1;
    int last = -1;


    for (int i = 0; i < n; i++)
    {
        if (speed.get(i) == maxSpeed)
        {
            if (first == -1)
            {
                first = i + 1;
            }

            last = i + 1;
        }
    }


    cout << "Максимальная скорость: " << maxSpeed << endl;


    if (first == last)
    {
        cout << "Номер автомобиля: " << first << endl;
    }
    else
    {
        cout << "Номера автомобилей: "
             << first << " и " << last << endl;
    }


    return 0;
}
