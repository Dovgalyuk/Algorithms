#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "list.h"

// Stack
// Stores pointer to custom user data
typedef char Data;
// Custom function to free user pointers on delete
typedef void (FFree)(void*);
typedef struct Stack {
    Data element;
    struct Stack *next;
} Stack;

typedef struct Stack Stack;
typedef struct Stack_operation {
    Data operation;
    struct Stack_operation *next;
} Stack_operation;

#ifdef __cplusplus
extern "C" {
    #endif

    Stack *create_stack_element(List_element **head, FFree f);
    Stack_operation *create_stack_operation(List_operation **head, FFree f);

    void stack_push_element(Stack **head, char elements);
    void stack_push_operation(Stack_operation **head, char operations);


    // Retrieves the last element from the stack
    Data stack_get(const Stack *stack);


    int stack_empty_operation(Stack_operation **head);
    Stack_operation *stack_peek_operation(Stack_operation **head);

    char stack_pop_operation(Stack_operation **head);
    char stack_pop_element(Stack **head);

    void free_stack_element(Stack **head);
    void free_stack_operation(Stack_operation **head);

    #ifdef __cplusplus
}
#endif

#endif
