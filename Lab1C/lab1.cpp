
#include "array.h"
#include <iostream>
using namespace std;


int flag = 0;

int first_task(const Array* arr,int a, int b) //Первое задание 
{
    int sum=0;
    for (size_t i=0; i<array_size(arr);i++)
    { 
      
       if (array_get(arr, i) % a == 0 || array_get(arr, i) % b == 0)
       {
           sum += array_get(arr, i);
       }
           
    }
    return sum;

}

/*
int second_task(const Array* arr)
{
    if (array_size(arr) < 5)
    {
       flag = 1;
    }

    int MaxEleIndex = 0;
    int sum = 0;
    for (size_t i = 0; i <4; i++)
    {
        sum += array_get(arr, i);
    }
    for (size_t i = 5; i < array_size(arr); i++)
    {

    }

    return MaxEleIndex;
}*/
size_t second_task(const Array* arr)
{
    int sum = 0;
 
    size_t size= array_size(arr);
    
    if (size< 5)
    {
        cout << "Array size is less than a 5 elements!" << endl;
        

    }
    else
    { 
        
        for (size_t i = 5; i < size; i++)
        {
            if (array_get(arr, i) > array_get(arr, i - 5))
            {
                
                sum += array_get(arr, i);
                cout << "Second task result: " << array_get(arr, i)<<endl;
                
            }
            else
            {
                
                sum += array_get(arr, i - 5);
                cout << "Second task result: " << array_get(arr, i-5)<<endl;
                
            }
            
        }
       
        
    }
    return 0;
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
    for (size_t i = 0; i < array_size(arr); i++)
    {
        array_set(arr, i, rand());
    }
    cout << "Enter a and b: ";  //Ввод чисел а и b
    cin >> a>> b;
    cout << endl;


    cout << "First task answer: "<<first_task(arr, a, b)<<endl; //Вывод результатов первого задания
    array_delete(arr);

    

    cout << "Enter size of array:";
    cin >> sizeofArr;
    Array* array = array_create(sizeofArr);
    for (size_t i = 0; i < array_size(array); i++)
    {
        array_set(array, i, rand());
    }
    second_task(array);
 
    array_delete(array);   //Удаление массива
    
    return 0;
}