#ifndef STACK_H
#define STACK_H

// Stack
// Stores integer values inside
typedef int Data;

struct Stack;

// Creates empty stack
Stack *stack_create();
Stack* stack_push(Stack* stack,Data data);
void stack_getStack(Stack* stack);
#endif
