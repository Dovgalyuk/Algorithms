#include <stdlib.h>
#include "stack.h"
#include "list.h"

typedef struct Stack {
    List *list;
} Stack;

Stack *stack_create(FFree f)
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->list = list_create(f);
    if (!stack->list) {
        free(stack);
        return NULL;
    }
    return stack;
}

void stack_delete(Stack *stack)
{
    if (!stack) return;
    
    list_delete(stack->list);
    free(stack);
}

void stack_push(Stack *stack, Data data)
{
    if(!stack) return;

    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    if (!stack) return (Data)0;
    if (!stack->list) return (Data)0;
    
    ListItem *num = list_first(stack->list);
    if (!num) return (Data)0;
    
    return list_item_data(num);
}

void stack_pop(Stack *stack)
{
    if (!stack || !stack->list) return;

    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    if (!stack) return true;
    if (!stack->list) return true;
    return list_first(stack->list) == NULL;
}
