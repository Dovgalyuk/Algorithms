#ifndef LAB1_H
#define LAB1_H
#include <cstdio>
#include "array.h"

int task1(Array *arr, FILE* input);
Array* task2(Array *arr, size_t &result_size);
Array* array_create_and_read(FILE *input);

#endif // LAB1_H
