#include "array.h"
#include <iostream>

using namespace std;


void task1(Array *arr)
{

    //Будем считать что в месяце в среднем 30 дней

    int sum = 0;
    int size = array_size(arr);
    if (size < 0 || size > 360)
    {
        cout << "Invalid value" << endl;
        return;
    }
    
    else {


    for (size_t i = 0; i < array_size(arr); i++)
    {
        sum += array_get(arr, i);
        switch (i)
        {
        case 29:
        {
            cout << "За январь выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 59:
        {
            cout << "За февраль выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 89:
        {
            cout << "За март выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 119:
        {
            cout << "За апрель выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 149:
        {
            cout << "За май выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 179:
        {
            cout << "За июнь выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 209:
        {
            cout << "За июль выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 239:
        {
            cout << "За август выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 269:
        {
            cout << "За сентябрь выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 299:
        {
            cout << "За октябрь выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 329:
        {
            cout << "За ноябрь выпало - " << sum << endl;
            sum = 0;
            continue;
        }
        case 359:
        {
            cout << "За декабрь выпало - " << sum << endl;
            sum = 0;
            continue;
        }

     }

    }

}
}

void task2(Array *arr)
    {
    char napr;
	cout << "Vvedite napravlenie sdviga l - left, r - right" << endl;
	cin >> napr;
    cout << endl;


	int pos;
    cout << "Vvedite chislo dlya sdviga" << endl;
	cin >> pos;
    cout << endl;

	int k = array_size(arr)-pos;
	int k2 = pos-1;

    int size = array_size(arr);


	if (pos >= 0 && pos <= size)
	{

	if (napr == 'l')
	{
	

	for (size_t i = 0; i < array_size(arr) ; i++)
    {
            array_set(arr, i, array_get(arr, i+pos));
			
			if (i == array_size(arr)-pos)
			{
				while(k < size)
				{
					array_set(arr, k, 0);
					k++;
				}
			}

			for (size_t j = 0; j < array_size(arr); j++)
			{
				cout <<"Index "<< j << " = " << array_get(arr, j) << endl;
			}
			cout << endl;

			if (i == array_size(arr)-pos)
				break;

    }
	
	}

	else if (napr=='r')
	{
		for (int j = array_size(arr)-1; j >= 0 ; j--)
		{
            array_set(arr, j, array_get(arr, j-pos));

			if (j == pos-1)
			{
				while (k2 >= 0)
				{
					array_set(arr, k2, 0); 
					k2--;
				}
				
			}
			
			for (size_t j = 0; j < array_size(arr); j++)
			{
				cout <<"Index "<< j << " = " << array_get(arr, j) << endl;
			}
			cout << endl;

			if (j == pos-1)
				break;


		}
    }
	else
	{
		cout << "Invalid direction value!" << endl;
		return;
	}
	}
	else
	{
		cout << "Invalid sdvig value!" << endl;
	}
    }
    

void CreateArray(Array *arr)
{
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand());
}


int main()
{
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL));
    Array *arr = NULL;
    size_t size;

    // create first array, release first task and delete first array
    cout << "Input a number from 1 to 360" << endl;
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task1(arr);
    array_delete(arr);

    // create second array, release second task and delete second array
    cout << "Input a size of array" << endl;
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task2(arr);
    array_delete(arr);

}