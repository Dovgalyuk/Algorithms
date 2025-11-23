#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdint.h>

// Stack
// Stores integer or pointer to custom user data
typedef uintptr_t Data;
// Custom function to free user pointers on delete
typedef void(FFree)(void *);

typedef struct Stack Stack;

#ifdef __cplusplus
extern "C" {
#endif

// Creates empty stack
Stack *stack_create(FFree f);

// Deletes the stack
void stack_delete(Stack *stack);

// Pushes data on top of the stack
// Should be O(1) on average
void stack_push(Stack *stack, Data data);

// Retrieves the last element from the stack
Data stack_get(const Stack *stack);

// Removes the last element from the stack
// Should be O(1)
void stack_pop(Stack *stack);

// Returns true if the stack is empty
bool stack_empty(const Stack *stack);

// Retrieves the bottom element from the stack
Data stack_get_bottom(const Stack *stack);

// Reverses the stack in place
void stack_reverse(Stack *stack);

// Concatenates all stack elements into one string
void stack_concat(Stack *stack);

// Removes the bottom element from the stack
void stack_remove_bottom(Stack *stack);

#ifdef __cplusplus
}
#endif

#endif
