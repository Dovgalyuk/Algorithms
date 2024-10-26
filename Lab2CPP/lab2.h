#ifndef LAB2_H_
#define LAB2_H_

#include "stack.h"
#include "vector.h"
#include <iostream>

void task1(FILE *input, Stack* stack, FILE* out);
void arithmetic_stack(Stack* stack, char symbol);
void inverse_stack(Stack* stack);
void comparison_stack(Stack* stack);
void dublicat_stack(Stack* stack);
void print_stack(Stack* stack, FILE* out);
void cin_stack(Stack* stack);

#endif // LAB2_H_