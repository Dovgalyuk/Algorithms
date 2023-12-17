#include <iostream>
#include "array.h"
#include <ctime>
#include <cstdint>
#include <queue>

using namespace std;

void task1(Array *arr)
{
    cout << "A) ";
    for (size_t i = 0; i < arr->size(); i++)
    {
        Data value = arr->get(i);
        if (value >= 10 && value <= 99)
            cout << value << ' ';
    }
    cout << endl
         << "B) ";
    for (size_t i = 0; i < arr->size(); i++)
    {
        Data value = arr->get(i);
        if (value >= 100 && value <= 999)
            cout << value << ' ';
    }
    cout << endl;
}

void task2(Array *arr)
{
    if (arr->size() < 5)
    {
        cout << "Array size is too small" << endl;
        return;
    }

    const int indsum = 5;
    int64_t sum = 0;

    for (size_t i=0; i < indsum; i++){
        sum += arr->get(i);
    }
    
    int64_t max = sum;

    for (size_t i = indsum; i < arr->size(); i++)
    {
        sum -= arr->get(i - 5);
        sum += arr->get(i);
        max = std::max(sum, max);
    }

    cout << "Max of 5: " << max << endl;
}

int main()
{
    srand(time(NULL));

    Array *arr = NULL;

    /* Create array here */

    size_t size;

    cout << "1) Enter size:";
    cin >> size;
    arr = new Array(size);
    for (size_t i = 0; i < arr->size(); i++)
        arr->set(i, rand() % 1000); // increases amount of need values

    task1(arr);

    delete arr;

    /* Create another array here */

    cout << "2) Enter size:";
    cin >> size;
    arr = new Array(size);
    for (size_t i = 0; i < arr->size(); i++)
        arr->set(i, rand());

    task2(arr);

    delete arr;
}
