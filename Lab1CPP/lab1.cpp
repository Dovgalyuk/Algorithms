#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

template <typename T>
Array<T> array_create_and_read(istream& input)
{
    size_t n;
    input >> n;
    /* Create array */
    Array<T> arr(n);
    /* Read array data */
    for (size_t i = 0 ; i < n ; ++i)
    {
        T x;
        input >> x;
        arr.set(i, x);
    }
    return arr;
}

template <typename T>
void task1(Array<T> &arr)
{

    T sumOneDecade = 0;
    T sumTwoDecade = 0;
    T sumThreeDecade = 0;

    for (size_t i = 0; i < 30; ++i)
    {
        if (i < 10)
            sumOneDecade += arr.get(i);
        if (i <= 19 && i > 9)
            sumTwoDecade += arr.get(i);
        if (i <= 29 && i > 19)
            sumThreeDecade += arr.get(i);
    }

    cout << sumOneDecade / 10 << endl;
    cout << sumTwoDecade / 10 << endl;
    cout << sumThreeDecade / 10 << endl;
}

template <typename T>
void task2(Array<T> &arr)
{
    bool unique = true;

    for (size_t i = 0; i < arr.size(); ++i)
    {
        unique = true;
        for (size_t j = 0; j < arr.size(); ++j)
        {
            if (i != j && arr.get(i) == arr.get(j))
            {
                unique = false;
                break;
            }
        }
        if (unique)
            cout << arr.get(i) << " ";
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    ifstream inputFile(argv[1]);

    Array<double> arr = array_create_and_read<double>(inputFile);
    task1(arr);

    Array<int> arr2 = array_create_and_read<int>(inputFile);
    task2(arr2);
}
