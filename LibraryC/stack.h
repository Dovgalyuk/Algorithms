#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef struct Stack_element {

   Data element;
   struct Stack_element *next;
} Stack_element;


typedef struct Stack_operation {

    Data operation;
    struct Stack_operation *next;
}Stack_operation;

#ifdef __cplusplus
extern "C" {
#endif


Stack_element *create_stack_element(List_element **head ,FFree f);
Stack_operation *create_stack_operation(List_operation **head ,FFree f);


void stack_push_element (Stack_element **head, char elements);
void stack_push_operation (Stack_operation **head, char operations);


int stack_empty_operation(Stack_operation **head);
Stack_operation *stack_peek_operation(Stack_operation **head);

char stack_pop_operation (Stack_operation **head);
char stack_pop_element (Stack_element **head);


Data stack_get_element(const Stack_element *stack);
Data stack_get_operation(const Stack_operation *stack);

void free_stack_element(Stack_element **head);
void free_stack_operation(Stack_operation **head);

#ifdef __cplusplus
}
#endif

#endif
