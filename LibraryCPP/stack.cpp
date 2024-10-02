#include "stack.h"
#include <iostream>
#include "list.h"

struct Stack
{
    List *list;
};

Stack *stack_create()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->list = list_create();  // Предполагается, что list_create также выделяет память
    }
    return stack;
}

void stack_delete(Stack *stack)
{
    if (stack != NULL) {
        list_delete(stack->list);
        free(stack);
    }
}

void stack_push(Stack *stack, Data data)
{
    if (stack != NULL) {
        list_insert(stack->list, data);
    }
}

Data stack_get(const Stack *stack)
{
    if (stack == NULL || stack->list == NULL || list_first(stack->list) == NULL) {
        // Ошибка: стек пуст или стек не существует
        return (Data)0;
    }
    return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
    if(stack != NULL)
        list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    if (stack != NULL && stack->list != NULL) {
        return list_first(stack->list) == NULL;
    }
    return true;
}
