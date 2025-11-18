#include <stdlib.h>
#include "stack.h"
#include "list.h"

typedef struct Stack {
    List* stack;
} Stack;

Stack *stack_create(FFree f)
{
    Stack* st = malloc(sizeof(Stack));
    if (st == NULL) 
        return NULL;

    st->stack = list_create(f);
    if (st->stack == NULL) {
        free(st);
        return NULL;
    }

    return st;
}

void stack_delete(Stack *stack)
{
    if (stack == NULL)
        return;

    list_delete(stack->stack);

    free(stack);
}

void stack_push(Stack *stack, Data data)
{
    if (stack == NULL || stack->stack == NULL) return;
    list_insert(stack->stack, data);
}

Data stack_get(const Stack *stack)
{
    if (stack == NULL || stack->stack == NULL) return (Data)0;

    ListItem* first = list_first(stack->stack);

    return list_item_data(first);
}

void stack_pop(Stack *stack)
{
    if (stack == NULL || stack->stack == NULL) return;

    if(list_first(stack->stack) != NULL)
        list_erase_first(stack->stack);
}

bool stack_empty(const Stack *stack)
{
    if (stack == NULL || stack->stack == NULL || list_first(stack->stack) == NULL) return true;
    else return false;
}
