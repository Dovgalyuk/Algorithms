#ifndef LAB1_H_
#define LAB1_h_

#include "array.h"
#include <iostream>

struct InputData{
    InputData(Array * arr,int a,int b){
        this->a=a;
        this->b=b;
        this->array=arr;
    }
    Array* array;
    int a;
    int b;
};
InputData array_create_and_read(FILE *input);
int task1(InputData inputArrAB);
int task2(Array *arr);

#endif // LAB1_H_
