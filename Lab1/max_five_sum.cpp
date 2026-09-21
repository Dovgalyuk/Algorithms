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

    Array<int> numbers(n);

    for (size_t i = 0; i < n; i++)
    {
        int value;
        file >> value;
        numbers.set(i, value);
    }

    long long sum = 0;

    for (size_t i = 0; i < 5; i++)
    {
        sum += numbers.get(i);
    }

    long long maxSum = sum;
    size_t position = 0;

    for (size_t i = 5; i < n; i++)
    {
        sum = sum - numbers.get(i - 5) + numbers.get(i);

        if (sum > maxSum)
        {
            maxSum = sum;
            position = i - 4;
        }
    }

    cout << "Максимальная сумма: " << maxSum << endl;

    cout << "Позиции пяти элементов: "
         << position + 1 << "-"
         << position + 5 << endl;

    cout << "Элементы: ";

    for (size_t i = position; i < position + 5; i++)
    {
        cout << numbers.get(i);

        if (i < position + 4)
        {
            cout << " ";
        }
    }

    cout << endl;

    return 0;
}
