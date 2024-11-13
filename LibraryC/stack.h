#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "list.h"

// Stack
// Stores pointer to custom user data
typedef char Data;
// Custom function to free user pointers on delete
typedef void (FFree)(void*);

typedef struct Stack Stack;


#ifdef __cplusplus
extern "C" {
    #endif

    Stack *create_stack(List_element **head, FFree f);
    void stack_push(Stack *stack, Data elements);
    Data stack_pop(Stack *stack);
    int stack_is_empty (Stack *stack);
    Data stack_get(const Stack *stack);
    void free_stack (Stack *stack);

    #ifdef __cplusplus
}
#endif

#endif
