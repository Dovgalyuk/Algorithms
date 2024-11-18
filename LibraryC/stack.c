#include "list.h"
#include "stack.h"

#include <stdlib.h>

struct List_element {
    Data element;
    struct List_element *next;
    FFree *distruct;
};

struct Stack {
    List_element *top;
    FFree *distruct;
};


Stack *create_stack(FFree f) {

    Stack *new_element = (Stack *)malloc(sizeof(Stack));
    if(NULL == new_element){
        return NULL;
    } else {
        new_element -> top = NULL;
        new_element -> distruct = f;
        return new_element;
    }
}


void stack_push(Stack *stack, Data elements) {

    add_list_element(&(stack -> top), elements);
}

Data stack_pop(Stack *stack) {

    return pop_list(&(stack -> top));
}

int stack_is_empty (Stack *stack) {

    return (stack -> top == NULL) ? 1:0;
}

void free_stack(Stack *stack) {

    delete_list_memory_element(&(stack -> top));
    free(stack);
}
Data stack_get(const Stack *stack) {

    if(NULL == stack || NULL == stack -> top){
        return '\0';
    } else {
        return stack -> top -> element;
    }
}
