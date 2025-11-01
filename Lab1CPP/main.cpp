#include <iostream>
#include <fstream>
#include "array.h"

long long factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;

    long long result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

int findMostFrequent(const Array& arr)
{
    int max_count = 0;
    int most_frequent = arr.get(0);
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr.get(j) == arr.get(i))
            {
                count++;
            }
        }
        if (count > max_count)
        {
            max_count = count;
            most_frequent = arr.get(i);
        }
    }
    return most_frequent;
}

int main(int argc, char* argv[])
{
    using namespace std;
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open())
    {
        cerr << "Failed to open file: " << argv[1] << endl;
        return 1;
    }

    // Задание 1: Чтение размера и заполнение факториалами
    int n;
    file >> n;
    Array arr1(n);

    for (int i = 0; i < n; i++)
    {
        arr1.set(i, factorial(i));
    }

    cout << "Factorial array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr1.get(i) << " ";
    }
    cout << endl;

    // Задание 2: Поиск наиболее частого элемента
    file >> n;
    Array arr2(n);

    for (int i = 0; i < n; i++)
    {
        int value;
        file >> value;
        arr2.set(i, value);
    }

    cout << "Most frequent element: " << findMostFrequent(arr2);

    return 0;
}