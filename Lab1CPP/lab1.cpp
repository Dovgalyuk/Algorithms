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
    int firstHalf=0,secondHalf=0;
    for(int i=0;i<15;i++){
        firstHalf += array_get(arr,i);
    }
    for(int i=15;i<30;i++){
        secondHalf += array_get(arr,i);
    }

    if(firstHalf>secondHalf){
        cout<<"Больше осадков выпало в первую половину июня"<<endl;
    } else if(firstHalf<secondHalf){
        cout<<"Больше осадков выпало во вторую половину июня"<<endl;
    } 

}

void task2(Array *arr)
{

}

int main(int argc, char **argv)
{ 
    setlocale(LC_ALL,"ru");

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