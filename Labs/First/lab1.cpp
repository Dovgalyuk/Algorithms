#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

void fill_array(Array* arr) {
    for (int i = 0; i < array_size(arr); i++) {
        array_set(arr,i, rand() % 10 + 1);
    }
}

void print_array(int num, int sizeArray, int i) {
    cout << num;
    if(i != sizeArray-1){
        if(i%2 == 0){
            cout << "-";
        } else{
            cout << "+";
        }
    }
}

int sum_elements(const Array* array){
    int sum = 0;
    cout << "Array: ";
    int sizeArray = array_size(array);
    for (int i = 0; i < sizeArray; i++){
        int num = array_get(array, i);
        if(i%2 == 0){
            sum += num;
        } else{
            sum -= num;
        }
        print_array(num, sizeArray, i);
    }
    return sum;
}

int main() {
    srand(time(0));
    int size;
    cout << "Array Size: ";
    cin >> size;
    Array* array = array_create(size);
    fill_array(array);
    int rez = sum_elements(array);
    cout << endl;
    cout << "Result: " << rez << endl;
    system("pause");
    array_delete(array);
}
