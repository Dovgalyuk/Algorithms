#include<iostream>
#include<fstream>
#include"array.h"

using namespace std;

Array* array_create_and_size(ifstream& input) {
    int n;
    input >> n;
    return array_create(n);
}

Array* array_create_and_read(ifstream& input)
{
    int n;
    input >> n;
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; i++)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

long long fac(int n) {
    long long res = 1;
    for (int i = 1; i <= n; i++)
        res *= i;
    return res;
}
void task1(Array* arr)
{
    size_t n = array_size(arr);
    for (size_t i = 0; i < n; i++)
        array_set(arr, i, (int)fac((int)i));

    cout << "Factorial: ";

    for (size_t i = 0; i < n; i++)
        cout << array_get(arr, i) << " ";

    cout << endl;
}

void task2(Array* arr)
{
    size_t n = array_size(arr);
    if (n < 5) {
        return;
    }

    int max = 0;
    size_t indx = 0;

    for (size_t i = 0; i <= n - 5; i++) {

        int tec = 0;

        for (size_t j = 0; j < 5; j++)
            tec += array_get(arr, i + j);

        if (tec > max) {
            max = tec;
            indx = i;
        }
    }

    cout << "Maximum sum: " << max << endl;
    cout << "Elements with maximum sum: ";
    for (int i = 0; i < 5; i++)
        cout << array_get(arr, indx + i) << " ";

}

int main(int argc, char** argv)
{
    (void)argc;
    Array* arr = nullptr;

    ifstream input(argv[1]);
    if (!input.is_open())
        return 1;

    arr = array_create_and_size(input);
    task1(arr);
    array_delete(arr);


    /* Create another array here */

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
 
    input.close();
}