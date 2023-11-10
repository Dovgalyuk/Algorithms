#include <iostream>
#include "array.h"

using namespace std;

void random(Array* arr){
    for(size_t i = 0; i < array_size(arr); i++){
        array_set (arr,i , Data(200 - rand() % 400));
    }
}

int Abs (int b) {
    if (b<0){
        return -b;
    } else {
        return b;
    }
}


void task1(Array* arr) {  
    random(arr);
    for (size_t i = 0; i < array_size(arr); i++){
       cout << array_get(arr,i) << '\t';
    }
    
    cout << '\n';
    double sum = 0;
    int a = 0;
    for (size_t i = 0; i < array_size(arr); i++){
         a++;
         sum += array_get(arr, i);
    }
    if( a != 0){
        sum /=a;
        cout << "avg: " << sum << '\n';
    }else{
        cout << "no elements\n";
    }
}

void task2(Array *arr)
{
    random (arr);

    for (size_t i=0; i<array_size(arr); i++){
        cout << array_get(arr,i) << '\t';
    }
    cout << '\n';
    int diff = 400, t = 0;
    size_t ArrSize = array_size(arr);
    for (size_t i=0; i < ArrSize; i++){
        int Num = array_get(arr,i);
        if (Num % 2 == 0) {
            t = Num;
            for (size_t j = i+1; j < ArrSize; j++){
                size_t nextNum = array_get(arr, j);
                if (nextNum % 2 == 0) {
                    int b = nextNum - t;
                    b = Abs(b);
                    if (diff> b && b !=0){
                        diff = b;
                    }
                }
            }
        }
    }
    if (diff == 400) {
        cout << "There are no 2 even numbers in the array " << '\n';
    }else{
        cout << "The minimum difference between different even numbers in array is: " << diff << '\n';
    }
}

int main()
{
   Array* arr = NULL;
    size_t size;

    cin >> size;
    arr = array_create(size);
    task1(arr);
    array_delete(arr);
    arr = NULL;

    cin >> size;
    arr = array_create(size);
    task2(arr);
    array_delete(arr);
}
