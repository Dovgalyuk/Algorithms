#include "array.h"
#include <iostream>
#include <string>

using namespace std;

int sum(Array *arr, int s1, int s2)
{
    //function for summing each month
    int summa = 0;

    for (int i = s1, j = s2; i <= j; i++)
    {
        summa += array_get(arr, i);
    }

    return summa;
}


void task1(Array *arr)
{
    //Будем считать что в месяце в среднем 30 дней

    size_t s1 = 0;
    size_t s2 = 29;

    static const string arrMonths[] = {"За январь выпало - ", "За февраль выпало - ", "За март выпало - ", "За апрель выпало - ",
    "За май выпало - ", "За июнь выпало - ", "За июль выпало - ", "За август выпало - ", "За сентябрь выпало - ", 
    "За октябрь выпало - ", "За ноябрь выпало - ", "За декабрь выпало - "};

    int sizeArrMonths = 12;

    for (int i = 0; i < sizeArrMonths; i++)
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
    delete(arrMonths);
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

    int size = array_size(arr);

    int zero1 = size - 1;
    int zero2 = 0;

	if (pos >= 0 && pos <= size)
	{
	    if (napr == 'l')
	    {
	        for(int j = 0; j < pos; j++)
            {
                for(int i = 1; i < size; i++)
                {
                    array_set(arr, i-1, array_get(arr, i));
                    if (i == zero1)
                    {
                        array_set(arr, i, 0);
                        zero1--;
                    }
                }
                for (int i = 0; i < size; i++)
                {
                    cout << array_get(arr, i) << endl;
                }
                cout << endl;
            }
	
	    }

	    else if (napr=='r')
	    {
		    for (int j = 0; j < pos; j++)
            {
                for (int i = size-2; i >= 0; i--)
                {
                    array_set(arr, i+1, array_get(arr, i));
                    if(i == zero2)
                    {
                        array_set(arr, i, 0);
                        zero2++;
                    }
                }
                for (int i = 0; i < size; i++)
                {
                    cout << array_get(arr, i) << endl;
                }
                cout << endl;
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