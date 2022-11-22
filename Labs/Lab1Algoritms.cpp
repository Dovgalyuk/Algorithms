

#include <iostream>
#include "array.h"
using namespace std;
//int main()
//{
//	setlocale(LC_ALL, "rus");
//	int size;
//	int sum = 0;
//	int composition = 1;
//	Data putArray; 
//	cin >> size;
//	Array* arr = array_create(size);
//	for (int i = 0; i < size; i++)
//	{
//		cin >> putArray;
//		array_set(arr, i, putArray);
//	}
//	
//
//	for (int i = 0; i <size; i++)
//	{
//		composition *= array_get(arr, i);
//		sum += array_get(arr, i);
//
//	}
//	cout <<"Сумма " << sum << ' ' << "Произведение " << composition;
//}


int main()
{
    Array* arr = array_create(10);

    if (array_size(arr) != 10)
    {
        std::cout << "Invalid array size\n";
        return 1;
    }

    for (int i = 0; i < 10; ++i)
        array_set(arr, i, i * 2);

    for (int i = 0; i < 10; ++i)
    {
        if (array_get(arr, i) != i * 2)
        {
            std::cout << "Invalid array element " << i << "\n";
            return 1;
        }
    }

    array_delete(arr);
}
