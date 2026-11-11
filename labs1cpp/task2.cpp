#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Укажите имя файла" << endl;
        return 1;
    }

    ifstream file(argv[1]);

    if (!file.is_open())
    {
        cout << "Файл не открыт" << endl;
        return 1;
    }

    int n;
    file >> n;

    if (!file || n <= 0)
    {
        cout << "Неправильный размер массива" << endl;
        return 1;
    }

    Array<int> arr(n);

    // Читаем элементы из файла
    for (int i = 0; i < n; i++)
    {
        int x;
        file >> x;

        if (!file)
        {
            cout << "Ошибка чтения элементов" << endl;
            return 1;
        }

        arr.set(i, x);
    }

    long long minDiff = -1;

    // Перебираем пары элементов
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int a = arr.get(i);
            int b = arr.get(j);

            if (a % 2 == 0 && b % 2 == 0 && a != b)
            {
                long long diff = a;
                diff = diff - b;

                if (diff < 0)
                {
                    diff = -diff;
                }

                if (minDiff == -1 || diff < minDiff)
                {
                    minDiff = diff;
                }
            }
        }
    }

    if (minDiff == -1)
    {
        cout << "Нет пары разных четных значений" << endl;
    }
    else
    {
        cout << minDiff << endl;
    }

    return 0;
}