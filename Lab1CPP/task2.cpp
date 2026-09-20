#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main(int argc, char* argv[])
{
    const char* filename = "input.txt";

    if (argc > 1)
    {
        filename = argv[1];
    }

    ifstream input(filename);

    if (!input.is_open())
    {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return 1;
    }

    size_t n;
    input >> n;

    Array* arr = array_create(n);

    int count[1001] = {};

    for (size_t i = 0; i < n; i++)
    {
        int value;
        input >> value;

        array_set(arr, i, value);
        count[value]++;
    }

    input.close();

    cout << "Элементы, встречающиеся только один раз:" << endl;

    for (size_t i = 0; i < n; i++)
    {
        int value = array_get(arr, i);

        if (count[value] == 1)
        {
            cout << value << " ";
        }
    }

    cout << endl;

    array_delete(arr);

    return 0;
}