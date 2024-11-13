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


Stack *create_stack(List_element **head ,FFree f) {

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

    List_element *new_element = (List_element *)malloc(sizeof(List_element));
    if(NULL == new_element){
        return;
    } else {
        new_element -> element = elements;
        new_element -> next = stack -> top;
        stack -> top = new_element;
    }
}

Data stack_pop(Stack *stack) {

    if(NULL == stack -> top){
        return '\0';
    } else {
        List_element *top_element = stack -> top;
        Data element = top_element -> element;
        stack -> top = top_element -> next;
        free(top_element);
        return element;
    }
}

int stack_is_empty (Stack *stack) {

    return (stack -> top == NULL) ? 1:0;
}

void free_stack (Stack *stack) {

    while(!stack_is_empty(stack)){
        List_element *top_element = stack -> top;
        stack -> top = top_element -> next;
        free(top_element);
    }
    free(stack);
}


Data stack_get(const Stack *stack) {

    if(NULL == stack || NULL == stack -> top){
        return '\0';
    } else {
        return stack -> top -> element;
    }
}
