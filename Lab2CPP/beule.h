#ifndef BEULE_H
#define BEULE_H

#include "stack.h"

void stack_dup(Stack* stack);
void stack_drop(Stack* stack);
void stack_swap(Stack* stack);
void stack_over(Stack* stack);
void stack_rot(Stack* stack);

#endif