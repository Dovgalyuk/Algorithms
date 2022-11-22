// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "array.h"
#include <string>

using namespace std;


int main()
{
    size_t size;
    Data addingElement;
    Data countNumbers2 = 0;
    Data countNumbers5 = 0;

    cout << "Input size: ";
    cin >> size;

    Array* arr = array_create(size);

    cout << "\n";

    for (size_t i = 0; i<size; i++)
    {
        cout << "Input element: ";
        cin >> addingElement;
        array_set(arr, i, addingElement);
    }

    for (size_t i = 0; i < size; i++)
    {
        if (array_get(arr, i) % 10 == 5) countNumbers5++;
        if (array_get(arr, i) % 2 == 0) countNumbers2++;
    }

    cout << "Kolichestvo chetnih chisel: " << countNumbers2 << "\n";
    cout << "Kolichestvo chisel kotorye okanchivaytsa na 5: " << countNumbers5 << "\n\n";

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
