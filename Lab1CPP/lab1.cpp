#include <stdio>
#include <algorithm>
#include "array.h"

using namespace std;

template <typename T>
Array<T> array_create_and_read(istream& input)
{
    int n;
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
    for (size_t i = 0; i < 30; ++i)
    {
        int sumOneDecade = 0;
        int sumTwoDecade = 0;
        int sumThreeDecade = 0;

        if (i < 10)
            sumOneDecade += arr.get(i);
        if (i < 19 && i > 9)
            sumTwoDecade += arr.get(i);
        if (i < 29 && i > 19)
            sumThreeDecade += arr.get(i);
    }

    cout << double(sumOneDecade / 10) << endl;
    cout << double(sumTwoDecade / 10) << endl;
    cout << double(sumThreeDecade / 10) << endl;
}

template <typename T>
void task2(Array<T> &arr)
{
    for (size_t k = 0; k < arr.size(); ++i)
    {
        for (size_t i = 0; i < arr.size() - 1; i++)
        {
            if (arr.get(i) > arr.get(i + 1))
                swap(arr.get(i), arr.get(i + 1));
        }
    }

    int temp = 0;

    for (size_t i = 0; i < arr.size() - 1; ++i)
    {
        temp = arr.get(i);
        if (arr.get(i + 1) != arr.get(i) && arr.get(i) != temp)
        {
            cout << temp << " ";
            count = 0;
        }
        else
            temp = arr.get(i);

    }

}

int main(int argc, char **argv)
{
    ifstream inputFile(argv[1]);

    Array<int> arr = array_create_and_read(inputFile);
    task1(arr);

    Array<int> arr2 = array_create_and_read(inputFile);
    task2(arr);
}
