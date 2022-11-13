#include <iostream>
#include "array.h"

using namespace std;

void rain(Array* arr, int const Size)
{
    int n = 0; // кол-во дней
    int mm = 0; // мм осадков всего
    for (int i = 0; i < Size; i++)
    {
        if (array_get(arr, i) > 0)
        {
            n++;
            mm += array_get(arr, i);
        }
    }
    cout << "В среднем, если шел дождь, в августе выпадало " << mm / n << " мм осадков в день"; // сразу подсчет ср. арифм.
}

int main()
{
    setlocale(LC_ALL, "RU");
    srand(time(NULL));
    int size;
    cout << "Введите длину массива: ";
    cin >> size;
    Array* mas = array_create(size);
    for (int i = 0; i < size; i++) // заполнение
    {
        array_set(mas, i, rand() % 31);
    }
    cout << "Наши сведения об осадках: ";
    for (int i = 0; i < size; i++) //  выводим массив для наглядности
    {
        cout << array_get(mas, i) << " ";
    }
    cout << endl;
    rain(mas, size);
    array_delete(mas);
}