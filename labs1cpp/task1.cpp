#include <iostream>
#include <fstream>
#include <climits>
#include "array.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Укажите имя файла" << endl;
        return 1;
    }

    ifstream file(argv[1]);

    if (!file.is_open())
    {
        cerr << "Файл не открыт" << endl;
        return 1;
    }

    int n;
    file >> n;

    if (!file  || n <= 0)
    {
        cerr << "Неправильный размер" << endl;
        return 1;
    }

    Array<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        int x;
        file >> x;

        if (!file )
        {
            cerr << "Неправильные элементы"<< endl;
            return 1;
        }

        arr.set(i, x);
    }

    int k1, k2;
    file >> k1 >> k2;
    if (!file )
    {
        cerr << "Неправильные номера элементов" << endl;
        return 1;
    }
    if (k1<1 || k1>n || k2<1 || k2>n){
        cerr<<"Номер за пределами массива "<<endl;
        return 1;
    }

    int a = arr.get(k1 - 1);
    int b = arr.get(k2 - 1);

    for (int i = 0; i < n; i++)
    {
        int x = arr.get(i);
        long long result = x;

        if (x > 0)
        {
            result = result - a;
        }
        else
        {
            result = result - b;
        }

        if (result < INT_MIN || result > INT_MAX)
        {
            cerr << "Переполнение int" << endl;
            return 1;
        }

        arr.set(i, (int)result);
    }

    for (int i = 0; i < n; i++)
    {
        if (i > 0)
        {
            cout << " ";
        }

        cout << arr.get(i);
    }

    cout << endl;
    return 0;
}