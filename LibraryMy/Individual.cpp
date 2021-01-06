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
    bool* rep = new bool[N];
    for (int i = 0; i < N; i++)
    {
        rep[i] = false;
    }
    for (int i = 0; i < N; i++) 
    {
        for (int j = i + 1; j < N; j++)
        {
            if (array_get(arr, i) == array_get(arr, j)) 
            {
                rep[i] = true;
                rep[j] = true;
                break;
            }
        }
    }
 
    for (int i = 0; i < N; i++)
    {
        if (rep[i] == false) cout << array_get(arr, i) << " ";
    }
}