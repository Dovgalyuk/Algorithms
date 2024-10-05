#ifndef STACK_H
#define STACK_H

// Stack
// Stores integer values inside
typedef int Data;

struct Stack;

// Creates empty stack
Stack *stack_create();

// Deletes the stack
void stack_delete(Stack *stack);

// Pushes data on top of the stack
// Should be O(1) on average
void stack_push(Stack *stack, Data data);

// Retrives the last element from the stack
Data stack_get(const Stack *stack);

// Removes the last element from the stack
// Should be O(1)
void stack_pop(Stack *stack);

// Returns true if the stack is empty
bool stack_empty(const Stack *stack);

void imul(Stack* stack);

void iadd(Stack* stack);

void isub(Stack* stack);

void il(Stack* stack, int ind);

void ist(Stack* stack, int ind, int si);

void swap(Stack* stack);

bool iand(Stack* stack);

bool ior(Stack* stack);

bool ixor(Stack* stack);

#endif
