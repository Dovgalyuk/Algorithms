#include <iostream>
#include <fstream>
#include "../LibraryCPPTemplate/array.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    ifstream file(argv[1]);

    if (!file)
    {
        return 1;
    }

    size_t n;
    file >> n;

    Array<int> speed(n);

    for (size_t i = 0; i < n; i++)
    {
        int value;
        file >> value;
        speed.set(i, value);
    }

    int maxSpeed = speed.get(0);
    int first = 0;
    int last = 0;

    for (size_t i = 1; i < n; i++)
    {
        if (speed.get(i) > maxSpeed)
        {
            maxSpeed = speed.get(i);
            first = i;
            last = i;
        }
        else if (speed.get(i) == maxSpeed)
        {
            last = i;
        }
    }

    cout << "Максимальная скорость: " << maxSpeed << endl;
    cout << "Первый автомобиль: " << first + 1 << endl;
    cout << "Последний автомобиль: " << last + 1 << endl;

    return 0;
}
