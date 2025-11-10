#include <iostream>
#include <fstream>
using namespace std;

// Проверка числа на простоту
bool isSimple(int num)
{
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

void task1()
{
    ifstream f("input_fill.txt");
    int n;
    f >> n;
    f.close();

    int* arr = new int[n];
    int count = 0;
    int num = 2;

    while (count < n)
    {
        if (isSimple(num))
        {
            arr[count] = num;
            count++;
        }
        num++;
    }

    cout << "Simple: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    delete[] arr;
}

void task2()
{
    ifstream f("input_shift.txt");
    int n;
    f >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        f >> arr[i];

    string dir;
    int steps;
    f >> dir >> steps;
    f.close();

    int* result = new int[n];
    for (int i = 0; i < n; i++)
        result[i] = 0;

    if (dir == "right")
    {
        for (int i = n - 1; i >= 0; i--)
        {
            if (i + steps < n)
                result[i + steps] = arr[i];
        }
    }
    else if (dir == "left")
    {
        for (int i = 0; i < n; i++)
        {
            if (i - steps >= 0)
                result[i - steps] = arr[i];
        }
    }

    cout << "shift: ";
    for (int i = 0; i < n; i++)
        cout << result[i] << " ";
    cout << endl;

    delete[] arr;
    delete[] result;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Укажите задачу: 1 - простые числа, 2 - сдвиг массива" << endl;
        return 1;
    }

    int choice = atoi(argv[1]);
    if (choice == 1)
        task1();
    else if (choice == 2)
        task2();
    else
        cerr << "Неверный выбор!" << endl;

    return 0;
}