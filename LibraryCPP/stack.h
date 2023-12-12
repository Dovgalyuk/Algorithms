#ifndef STACK_H
#define STACK_H

// Stack
// Stores integer values inside
typedef int Data;

struct Stack;

// Creates empty stack
Stack *stack_create();
void stack_push(Stack* stack,Data data);
Data stack_getStack(Stack* stack);
void stack_delete(Stack* stack); 
bool stack_empty(Stack* stack);
void stack_pop(Stack* stack);
#endif
