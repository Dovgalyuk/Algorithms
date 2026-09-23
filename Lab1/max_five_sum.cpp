#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;


int main(int argc, char* argv[])
{
    if (argc < 2)
        return 1;

    ifstream file(argv[1]);

    if (!file)
        return 1;


    int n;
    file >> n;


    Array<int> numbers(n);

    for (int i = 0; i < n; i++)
    {
        int value;
        file >> value;
        numbers.set(i, value);
    }


    int currentSum = 0;

    for (int i = 0; i < 5; i++)
    {
        currentSum += numbers.get(i);
    }


    int maxSum = currentSum;
    int position = 0;


    for (int i = 5; i < n; i++)
    {
        currentSum += numbers.get(i);
        currentSum -= numbers.get(i - 5);


        if (currentSum > maxSum)
        {
            maxSum = currentSum;
            position = i - 4;
        }
    }


    cout << "Максимальная сумма: "
         << maxSum << endl;


    cout << "Позиции пяти элементов: "
         << position + 1 << "-"
         << position + 5 << endl;


    cout << "Элементы: ";

    for (int i = 0; i < 5; i++)
    {
        if (i != 0)
            cout << " ";

        cout << numbers.get(position + i);
    }

    cout << endl;


    return 0;
}
