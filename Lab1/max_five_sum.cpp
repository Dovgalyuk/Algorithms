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


    int maxSum = numbers.get(0)
               + numbers.get(1)
               + numbers.get(2)
               + numbers.get(3)
               + numbers.get(4);


    int position = 0;


    for (int i = 1; i <= n - 5; i++)
    {
        int sum = 0;

        for (int j = 0; j < 5; j++)
        {
            sum += numbers.get(i + j);
        }


        if (sum >= maxSum)
        {
            maxSum = sum;
            position = i;
        }
    }


    cout << "Максимальная сумма: " << maxSum << endl;

    cout << "Позиции пяти элементов: "
         << position + 1 << "-"
         << position + 5 << endl;


    cout << "Элементы: ";

    for (int i = 0; i < 5; i++)
    {
        if (i != 0)
        {
            cout << " ";
        }

        cout << numbers.get(position + i);
    }

    cout << endl;


    return 0;
}
