
#include "array.h"
#include <iostream>
using namespace std;




int first_task(const Array* arr,int a, int b) //Первое задание 
{
    int sum=0;
    for (int i=0; i<array_size(arr);i++)
    { 
      
       if (array_get(arr, i) % a == 0 || array_get(arr, i) % b == 0)
       {
           sum += array_get(arr, i);
       }
           
    }
    return sum;

}

int second_task(const Array* arr)
{
    if (array_size(arr) < 5)
    {
        return -1;
    }
    int maxSum = 0;
    int MaxEleIndex = 0;
    for (int i = 0; i < array_size(arr) - 5; i++)
    {
        int sum = 0;
        for (int j = i; j < i + 5; j++)
        {
            sum += array_get(arr, j);
        }
        if (sum > maxSum)
        {
            maxSum = sum;
            MaxEleIndex = i;
        }
    }
    
    return MaxEleIndex;
}
 

int main()
{
    setlocale(LC_ALL, "Russian");
    size_t sizeofArr;
    int a, b;
    cout << "Enter size of array:";
    cin >> sizeofArr;   
    cout << endl;
    Array* arr= array_create(sizeofArr); //Создание экземпляра массива


    srand(time(NULL) % 100);            //Генератор случайных чисел
    for (int i = 0; i < array_size(arr); i++)
    {
        array_set(arr, i, rand());
    }
    cout << "Enter a and b: ";  //Ввод чисел а и b
    cin >> a>> b;
    cout << endl;


    cout << "First task answer: "<<first_task(arr, a, b)<<endl; //Вывод результатов первого задания

    if (second_task(arr) == -1)                       //Вывод результатов второго задания
    {
        cout << "Size of array is less than 5 elements." << endl;
    }
    else
    {
        for (int i = second_task(arr); i < second_task(arr) + 5; i++)
        {
            cout << "Second task answer:" <<  array_get(arr, i) << endl;
        }
    }
 
    array_delete(arr);   //Удаление массива
    
    return 0;
}