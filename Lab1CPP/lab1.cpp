#include <iostream>
#include <fstream>
#include <string>
#include "array.h"

using namespace std;

Array *array_create_and_write(ifstream& input)
{
    int n;
    input >> n;
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr){
    if (arr == nullptr) return;
    
    int sum = 0;
    size_t size = array_size(arr);
    size_t rainday = size;
    for(size_t i = 0; i < size; i++){
        sum += array_get(arr, i);
        if (array_get(arr, i) == 0) {
            rainday--;
        }
    }
    if (rainday == 0) {
        cout << "0,0 "; 
    }
    else {
        cout << sum / rainday << "," << (sum % rainday) << " ";
    }
}

void task2(Array *arr){
    if (arr == nullptr) return;

    for (size_t i = 0; i < array_size(arr) - 1; i++) {
        for (size_t j = 0; j < array_size(arr) - i - 1; j++) {
            if (array_get(arr, j) > array_get(arr, j + 1)) {
                int temp = array_get(arr, j);
                array_set(arr, j, array_get(arr, j + 1));
                array_set(arr, j + 1, temp);
            }
        }
    }

    for (size_t i = 0; i < array_size(arr)-1; i++) {
        if (array_get(arr, i)==array_get(arr, i+1)) {
            for (size_t g = i++; g < array_size(arr); g++)
            {
                if (array_get(arr, g) == array_get(arr, i))
                    i++;
                else
                    g = array_size(arr);
            }
        }
        else
        {
            cout << array_get(arr, i) << " ";
        }
    }
    if(array_get(arr, array_size(arr)-2)!=array_get(arr, array_size(arr)-1))
        cout<<array_get(arr, array_size(arr)-1)<<" ";
}

int main(){
    ifstream input("input.txt");

    Array *arr = array_create_and_write(input);
    
    task1(arr);
    array_delete(arr);
    
    
    /* Create another array here */
    arr = array_create_and_write(input);
    
    task2(arr);
    array_delete(arr);
    input.close();
}
