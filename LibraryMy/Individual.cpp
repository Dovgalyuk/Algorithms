#include <iostream>
#include "array.h"

typedef Array* MyArray;
using namespace std;

int main()
{
    srand(4541);
    int N = -1;
    cout << "Size of array (must be positive): ";
    cin >> N;
    MyArray arr = array_create(N);
    const int random_limit = 20;
    for (int i = 0; i < N; i++)
    {
        array_set(arr, i, rand() % random_limit);
    }
    for (int i = 0; i < N; i++) 
    {
        int rep = 1;
        for (int j = 0; j < N; j++)
        {
            if (array_get(arr, i) == array_get(arr, j) && i != j) 
            {
                rep = 0;
                break;
            }
        }
        if (rep == 1)
        {
            cout << array_get(arr, i) << " ";
        }
    }
}