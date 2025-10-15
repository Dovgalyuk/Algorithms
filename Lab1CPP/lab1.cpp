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
    cout << sum / rainday << "," << (sum % rainday) << " ";
}

void task2(Array *arr){
    if (arr == nullptr) return;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        if (arr[i]==arr[i++]) {
            for (int g = i++; g < n; g++)
            {
                if (arr[g] == arr[i])
                    i++;
                else
                    g = n;
            }
        }
        else
        {
            cout << arr[i] << " ";
        }
    }
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
