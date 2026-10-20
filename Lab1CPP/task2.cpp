#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Usage: Task2 <input file>" << endl;
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
    if (n < 5)
    {
        cout << "The array has less than five elements" << endl;
        return 1;
    }

    Array *arr = array_create(n);

    for (int i = 0 ; i < n ; ++i)
    {
        Data x;
        input >> x;
        array_set(arr, i, x);
    }

    long long current_sum = 0;
    for (int i = 0 ; i < 5 ; ++i)
        current_sum += array_get(arr, i);

    long long best_sum = current_sum;
    int best_index = 0;

    for (int i = 1 ; i <= n - 5 ; ++i)
    {
        current_sum -= array_get(arr, i - 1);
        current_sum += array_get(arr, i + 4);

        if (current_sum > best_sum)
        {
            best_sum = current_sum;
            best_index = i;
        }
    }

    cout << "Maximum sum: " << best_sum << endl;
    cout << "Indices:";
    for (int i = 0 ; i < 5 ; ++i)
        cout << " " << best_index + i;
    cout << endl;

    cout << "Values:";
    for (int i = 0 ; i < 5 ; ++i)
        cout << " " << array_get(arr, best_index + i);
    cout << endl;

    array_delete(arr);
    return 0;
}
