#include "stack.h"
#include "list.h"
#include <cstddef>

using namespace std;
struct Stack
{
    List* data;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->data = list_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->data);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->data, data);
}

Data stack_get(const Stack *stack)
{
    return list_item_data(list_first(stack->data));
}

void stack_pop(Stack *stack)
{
    list_erase(stack->data,list_first(stack->data));
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->data) == NULL;
}
