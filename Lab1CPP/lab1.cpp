#include <iostream>
#include <fstream>
#include "array.h"

//
Array *array_create_and_read(std::ifstream &input)
{
    int n;
    input >> n;
    
    //создание массива
    Array *arr = array_create(n); 
  
    for(int i = 0; i < n; i++)
    { 
        int x;
        input >> x;
         //присваивание указанному элементу значение
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr, size_t size)
{ 
    double positive = 0;
    double negative = 0;
    int CountP = 0;
    int CountN = 0;

    for (size_t i = 0; i < size; i++){
        int value = array_get(arr, i);

        if (value > 0){
            positive += value;
            CountP++;
        }
        else if (value < 0){
            negative += value;
            CountN++;
        }
    }
    
    double averageP = positive/CountP;
    double averageN = negative/CountN;

    std::cout << averageP << " " << averageN << std::endl;
}

void task2(Array *arr)
{
    size_t size = array_size(arr);
    int often = 0;
    int maxCount = 0;

    for (size_t i = 0; i < size; i++){
        int current = array_get(arr, i);
        int count = 0;

        for (size_t j = 0; j < size; j++){
            if (array_get(arr, j) == current)
            count++;
        }

        if (count > maxCount){
            maxCount = count;
            often = current;
        }
    }

    std::cout << often << std::endl;
}

int main(int argc, char **argv)
{ 
    Array *arr = NULL;
    std::ifstream input(argv[1]);
    arr = array_create_and_read(input);

    task1(arr, array_size(arr));   // размер массива
    array_delete(arr);

    /* Create another array here - создать еще один массив*/
    arr = array_create_and_read(input);
   
    task2(arr);
    array_delete(arr);

    input.close();
}