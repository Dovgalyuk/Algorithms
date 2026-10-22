#ifndef STACK_H
#define STACK_H

#include "list.h"

// Stack

struct Stack;

// Creates empty stack
Stack *stack_create();


void stack_delete(Stack *stack);

void stack_push(Stack *stack, Data data);

// Retrieves the last element from the stack
Data stack_get(const Stack *stack);

// Removes the last element from the stack
// Should be O(1)
void stack_pop(Stack *stack);

// Returns true if the stack is empty
bool stack_empty(const Stack *stack);

#endif