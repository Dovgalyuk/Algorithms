#include <stdlib.h>
#include "stack.h"

struct Stack {
    List *list;
};

// Creates empty stack
Stack *stack_create() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->list = list_create();
    return stack;
}

// Deletes the stack
void stack_delete(Stack *stack) {
    list_delete(stack->list);
    free(stack);
}

// Pushes data on top of the stack
void stack_push(Stack *stack, Data data) {
    list_insert(stack->list, data);
}

// Retrieves the last element from the stack
Data stack_get(const Stack *stack) {
    return list_item_data(list_first(stack->list));
}

// Removes the last element from the stack
void stack_pop(Stack *stack) {
    list_erase_first(stack->list);
}

// Returns true if the stack is empty
bool stack_empty(const Stack *stack) {
    return list_first(stack->list) == NULL;
}