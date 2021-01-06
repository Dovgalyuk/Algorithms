#include <iostream>
#include "array.h"
using namespace std;

bool* find_entry(Array* arr, size_t n)
{
    size_t* entry = new size_t[n];

    for (int i = 0; i < n; i++)
    {
        entry[i] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (array_get(arr, i) == array_get(arr, j))
            {
                entry[i]++;
                entry[j]++;
            }
        }
    }

    bool* entry_2 = new bool[n];
    for (int i = 0; i < n; i++)
    {
         entry_2[i] = entry[i] == 2;
    }
    delete[] entry;
    return entry_2;
}

int main()
{
	cout << "size of array: ";
	size_t size;
	cin >> size;
	srand(2000);
	Array* arr = array_create(size);
	for (int i = 0; i < size; i++)
	{
		array_set(arr, i, rand() % 10);
	}
    bool* entry_2 = find_entry(arr, size);
	for (int i = 0; i < size; i++)
	{
		if (entry_2[i] == true)
		{
            cout << array_get(arr, i) << ' ';
		}
	}

    array_delete(arr);
    delete[] entry_2;
}