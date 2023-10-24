#include <iostream>
#include <ctime>
#include "array.h"
#include "math.h"

using namespace std;

struct Array
{
    size_t size;
    Data* data;
};

//Ввести целое число с клавиатуры
//создать массив такой размерности и заполнить его случайными числами.
//Найти сумму всех цифр всех чисел массива.
void task1(Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++){ //random initialization array
        array_set(arr, i, rand());
    }

    size_t count = 0;
    size_t num = 0;
    cout << "Array: ";
    for (size_t i = 0; i < array_size(arr); i++)
    {
        cout << array_get(arr, i);
        if (i != array_size(arr)-1) cout  << ' ';

        num = array_get(arr, i);
        for (; num!= 0; num/=10){
            count+=num%10;
        }
    }
    cout <<"\nSum of all digits of all array numbers - " << count << endl;
}


//Ввести целое число с клавиатуры
//создать массив такой размерности и заполнить его случайными числами.
//Найти минимальную разность между разными чётными элементами массива.
void task2(Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
        array_set(arr, i, rand() % 202 - 101);

    cout << "Array: ";
    for (size_t i = 0; i < array_size(arr); i++){
        cout << array_get(arr, i);
        if (i != array_size(arr)-1) cout  << ' ';
    }

    Array *tempArr = array_create(array_size(arr));
    size_t evenElemCounter = 0;
    for (size_t i = 0; i < array_size(arr); i++)
        if (arr->data[i] % 2 == 0)
            array_set(tempArr, evenElemCounter++, array_get(arr, i));
    
    if (evenElemCounter < 2)
    {
        cout << endl << "Not enough even elements.";
        return;
    }

    int minDif = abs(array_get(tempArr, 0) - array_get(tempArr, 1));
    int curDif;
    for (size_t i = 0; i < evenElemCounter - 1; i++)
    {
        for (size_t j = i + 1; j < evenElemCounter; j++)
        {
            curDif = abs(array_get(tempArr, i) - array_get(tempArr, j));
            if (minDif > curDif)
                minDif = curDif;
        }
    }
    array_delete(tempArr);

    cout << endl << "Minimum difference of even elements: " << minDif;
}

int main()
{
    srand((int)time(NULL));
    size_t size;

    Array *arr = NULL;
    /* Create array here */
    cout << "Enter array size - ";
    cin >> size;
    arr = array_create(size);

    task1(arr);
    array_delete(arr);

    /* Create another array here */
    cout << "Enter array size - ";
    cin >> size;
    arr = array_create(size);

    task2(arr);
    array_delete(arr);
}