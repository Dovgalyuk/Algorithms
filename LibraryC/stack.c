#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct Stack {
    List *list; // underlying list
};

Stack *stack_create(FFree f)
{
    Stack *s = (Stack*)malloc(sizeof(Stack));
    if (!s) return NULL;
    s->list = list_create(f);
    if (!s->list) { free(s); return NULL; }
    return s;
}

void stack_delete(Stack *stack)
{
    if (!stack) return;
    list_delete(stack->list);
    free(stack);
}

void stack_push(Stack *stack, Data data)
{
    if (!stack) return;
    list_insert(stack->list, data); // insert at head is top
}

Data stack_get(const Stack *stack)
{
    if (!stack || !list_first(stack->list)) return (Data)0;
    return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
    if (!stack) return;
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    return !stack || list_first(stack->list) == NULL;
}
