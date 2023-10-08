#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int sumMultiples(int* arr, int size, int a, int b){
    int sum=0;
    for(int i=0; i<size;i++){
        if(arr[i] % a==0 || arr[i] % b==0){
            sum+=arr[i];
        }
    }
    return sum;
}

int sumBetweenminmax(int* arr,int size){
    if(size<2){
        return 0; // если размер массива меньше двух то сумма будет 0
    }

int minIndex=0;
int maxIndex=0;

 for (int i = 1; i < size; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    int sum=0;
    if(minIndex<maxIndex){
        for(int i=minIndex+1; i<maxIndex;i++){
            sum+=arr[i];
        }
    }else {
        for(int i=maxIndex+1; i<minIndex;i++){
            sum+=arr[i];
        }
    }
    return sum;
}

int main(){
    srand(time(0));
    setlocale(LC_ALL,"RU");
    int size,a,b;

    cout<<"Введите размер массива: ";
    cin>> size;

    int* arr=new int[size];
    for(int i=0; i<size; i++){
        arr[i]=rand()%100; //заполнение массива случайными числами от 0 до 99
    }
    cout<<"Введите числа a и b: ";
    cin>> a >> b;

    int sumMultiplesRes=sumMultiples(arr,size,a,b);
    
    cout<<"Сумма элементов массива, кратных " << a << " или " << b << " = " << sumMultiplesRes << endl;
    delete[] arr;
    return 0;
}