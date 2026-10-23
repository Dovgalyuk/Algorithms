#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Usage: Task1 <input file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open())
    {
        cout << "Cannot open file " << argv[1] << endl;
        return 1;
    }

    int n;
    input >> n;
    if (n <= 0)
    {
        cout << "Invalid array size" << endl;
        return 1;
    }

    Array *arr = array_create(n);

    for (int i = 0 ; i < n ; ++i)
    {
        Data x;
        input >> x;
        array_set(arr, i, x);
    }

    long long sum = 0;
    for (int i = 0 ; i < n ; ++i)
        sum += array_get(arr, i);

    int count = 0;
    for (int i = 0 ; i < n ; ++i)
    {
        if (array_get(arr, i) > sum)
            ++count;
    }

    cout << "Sum of all elements: " << sum << endl;
    cout << "Number of elements greater than sum: " << count << endl;
    cout << "Their indices:";

    if (count == 0)
        cout << " none";
    else
    {
        for (int i = 0 ; i < n ; ++i)
        {
            if (array_get(arr, i) > sum)
                cout << " " << i;
        }
    }

    cout << endl;

    array_delete(arr);
    return 0;
}
