#ifndef STACK_H
#define STACK_H

// Stack
// Stores integer values inside
typedef int Data;

struct Stack;

// Creates empty stack
Stack* stack_create();

// Deletes the stack
void stack_delete(Stack* stack);

// Pushes data on top of the stack
// Should be O(1) on average
void stack_push(Stack* stack, Data data);

// Retrives the last element from the stack
Data stack_get(const Stack* stack);

// Removes the last element from the stack
// Should be O(1)
void stack_pop(Stack* stack);

// Returns true if the stack is empty
bool stack_empty(const Stack* stack);

#endif
