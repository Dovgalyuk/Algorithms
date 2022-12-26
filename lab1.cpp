#include <iostream>
#include "array.h"
#include <ctime> 

using namespace std;
int main()
{
    int n;
    cin >> n;
    Array *arr = array_create(n);
    srand(time(0));

    for (int i = 0; i < n; i++) {
        array_set(arr, i, 1 + rand() % 100);
    }
    
    int max1 = 0;
    for (int i = 0 ; i <= n - 5; ++i)
    {
            max1 = max(
                max1,
                array_get(arr, i) +
                array_get(arr, i + 1) +
                array_get(arr, i + 2) +
                array_get(arr, i + 3) +
                array_get(arr, i + 4)
            );

    }
     cout << max1;

    array_delete(arr); 
}
