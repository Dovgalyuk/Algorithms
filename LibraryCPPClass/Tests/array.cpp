#include <iostream>
#include "array.h"

using namespace std;

int main()
{
    Array *arr = new Array(10);

    if (arr->size() != 10)
    {
        cout << "Invalid array size\n";
        return 1;
    }

    for (int i = 0 ; i < 10 ; ++i)
        arr->set(i, i * 2);

    Array copy(*arr);

    for (int i = 0 ; i < 10 ; ++i)
    {
        if (arr->get(i) != i * 2
            || copy.get(i) != i * 2)
        {
            cout << "Invalid array element " << i << "\n";
            return 1;
        }
    }


    try {
        arr->set(32, 8);
        cout << "[TEST #1] - set() check for invalid index\t\nResult: set() doesn't handle invalid index\n";
        return 1;
    }
    catch (const out_of_range&) {
        cout << "[TEST #1] - set() check for invalid index\t\nResult: Caught expected out_of_range exception for set() with invalid index\n";
    }

    try {
        arr->get(16);
        cout << "[TEST #2] - get() check for invalid index\t\nResult: set() doesn't handle invalid index\n";
        return 1;
    }
    catch (const out_of_range&) {
        cout << "[TEST #2] - get() check for invalid index\t\nResult: Caught expected out_of_range exception for get() with invalid index\n";
    }

    delete arr;
}

