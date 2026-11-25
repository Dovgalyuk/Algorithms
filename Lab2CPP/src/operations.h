#ifndef ASISTAINT_H
#define ASISTAINT_H

#include "stack.h"

void stackPush(const int &value, Stack *stack);
int stackPop(const char letter, Stack *stack);

void addionFunction(Stack *stack);
void subtractionFunction(Stack *stack);
void multiplicationFunction(Stack *stack);

#endif