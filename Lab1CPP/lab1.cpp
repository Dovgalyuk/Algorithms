#include <iostream>
#include <fstream>
#include "array.h"
using namespace std;

Array *array_create_and_read(std::ifstream &input)
{
    int n;
    input >> n;
    
    Array *arr = array_create(n);
  
    for(int i = 0; i < n; i++)
    { 
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{ 
    size_t n=array_size(arr);
    if(n!=30){
        return ;
    }
    //a
    int firstHalf=0,secondHalf=0;
    for(int i=0;i<15;i++){
        firstHalf += array_get(arr,i);
    }
    for(int i=15;i<30;i++){
        secondHalf += array_get(arr,i);
    }

    if(firstHalf>secondHalf){
        cout<<1<<endl;
    } else if(firstHalf<secondHalf){
        cout<<2<<endl;
    } 
    //b
    int dec1=0, dec2=0, dec3=0;
    for(int i=0;i<10;i++){
        dec1 += array_get(arr,i);
    }
    for(int i=10;i<20;i++){
        dec2 += array_get(arr,i);
    }
    for(int i=20;i<30;i++){
        dec3 += array_get(arr,i);
    }

    if(dec1>dec2 && dec1>dec3){
        cout<<1<<endl;
    }else if(dec2>dec1 && dec2>dec3){
        cout<<2<<endl;
    }else if(dec3>dec2 && dec3>dec1){
        cout<<3<<endl;
    }

}

void task2(Array *arr)
{
    int n=array_size(arr);
    for(int i=0;i<n;i++){
        int num = array_get(arr,i);
        bool unique = true;
        for(int j=0;j<n;j++){
            if(i!=j && array_get(arr,j)==num){
            unique = false;
            break;
            }
        }
        if(unique){
            cout<<num<<endl;
        }
    }

}

int main(int argc, char **argv)
{ 
    Array *arr = NULL;
    std::ifstream input(argv[1]);
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    input.close();
}