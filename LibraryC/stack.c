#include <stdlib.h>
#include "stack.h"
#include "list.h"

typedef struct Stack
{
    List* list;
} Stack;

Stack *stack_create(FFree f)
{
    Stack* stack = malloc(sizeof(Stack));
    if (stack) {
        stack->list = list_create(f);
    }
    return stack;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->list);
    free(stack);
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    ListItem* first_item = list_first(stack->list);
    if (first_item) {
        return list_item_data(first_item);
    }
    return (Data)0;
}

void stack_pop(Stack *stack)
{
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list) == NULL;
}
