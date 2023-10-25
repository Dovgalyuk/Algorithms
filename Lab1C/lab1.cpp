#include "array.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int sum(Array *arr, int s1, int s2)
{
    //function for summing each month
    int summa = 0;

    for (int i = s1, j = s2; s1 <= s2; s1++)
    {
        summa += array_get(arr, i);
    }

    return summa;
}


void task1(Array *arr)
{
    //Будем считать что в месяце в среднем 30 дней

    int s1 = 0;
    int s2 = 29;

    vector<string> arrMonths = {"За январь выпало - ", "За февраль выпало - ", "За март выпало - ", "За апрель выпало - ",
    "За май выпало - ", "За июнь выпало - ", "За июль выпало - ", "За август выпало - ", "За сентябрь выпало - ", 
    "За октябрь выпало - ", "За ноябрь выпало - ", "За декабрь выпало - "};

    for (int i = 0; i < arrMonths.size(); i++)
    {
        int summa = sum(arr, s1, s2);
        cout << arrMonths[i] << summa << endl;
        s1 += 30;
        s2 += 30;
        if (s2 > array_size(arr))
        {
            break;
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

	int k2 = pos-1;
    int size = array_size(arr);
    int k = size - pos;

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