
#include "array.h"
#include <iostream>
using namespace std;


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


size_t second_task(const Array* arr)
{
    int sum = 0;
    int summax = 0;
    size_t indx = 0;
    size_t size = array_size(arr);

    if (size < 5)
    {
        cout << "Array size is less or equal to 5 elements!" << endl;
        return 0;
        
    }
    else if (size == 5)
    {
        for (size_t i = 0; i < 5; i++)
        {
            sum += array_get(arr, i);
        }
        summax = sum;
        indx = 5;
    }
    else if (size > 5)
    {
        for (size_t i = 0; i < 5; i++)
        {
            sum += array_get(arr, i);
            if (sum > summax)
            {
                summax = sum;
                
            }
        }
        indx = 5;

        for (size_t i = 5; i < size; i++)
        {
            if (sum > summax)
            {
                summax = sum;
                indx = i;

            }
  
                sum += array_get(arr, i);
                sum -= array_get(arr, i - 5);

        }
    }
    return indx-5;
}


int main()
{
    
    setlocale(LC_ALL, "Russian");
    size_t sizeofArr1;
    size_t indx;
    int a, b;
    cout << "Enter size of array:";
    cin >> sizeofArr1;   
    cout << endl;
    Array* arr= array_create(sizeofArr1); //Создание экземпляра массива

    
    srand(time(NULL) % 100);            //Генератор случайных чисел
    for (size_t i = 0; i < array_size(arr); i++)
    {
        array_set(arr, i, rand());
        
    }
    cout << "Enter a and b: ";  //Ввод чисел а и b
    cin >> a>> b;
    cout << endl;


  cout << "First task answer: "<<first_task(arr, a, b)<<endl; //Вывод результатов первого задания
    array_delete(arr); //Удаление массива

    
    size_t sizeofArr2;
    cout << "Enter size of array: ";
    cin >> sizeofArr2;  //Ввод данных
    Array* array = array_create(sizeofArr2); //Создание экземпляра массива
    int g;
    for (size_t i = 0; i < array_size(array); i++)
    {
        cin >> g;
        array_set(array, i, g);

    }
   
   indx = second_task(array);
   if (indx < 5)
   {
       for (size_t i = 0; i < 5; i++)
       {
           cout << "Second task answer: " << array_get(array, i) << endl; 
       }
   }
   else if (indx + 5 == array_size(array)-1)
   {
       for (size_t i = array_size(array)-1; i >indx; i--)
       {
           cout << "Second task answer: " << array_get(array, i) << endl; 
       }
   }
   else
   {
       for (size_t i = indx; i<indx+5; i++)
       {
           cout << "Second task answer: " << array_get(array, i) << endl; 
       }
   }
   
   
   array_delete(array);   //Удаление массива        
    
    
    
}
    