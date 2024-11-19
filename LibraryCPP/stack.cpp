#include "stack.h"
#include "list.h"
#include <stdexcept>

using namespace std;

struct Stack
{
    List* list;
};

Stack *stack_create()
{
    Stack* newStack = new Stack;
    newStack->list = list_create();
    return newStack;
}

void stack_delete(Stack *stack)
{
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
    if (stack_empty(stack)) {
        throw runtime_error("Stack is empty");
    }
    ListItem* item = list_first(stack->list);
    Data data = list_item_data(item);
    return data;
}

void stack_pop(Stack *stack)
{
    if (stack_empty(stack)) {
        throw runtime_error("Stack is empty");
    }
    list_erase_first(stack->list);
}

bool stack_empty(const Stack *stack)
{
    return list_first(stack->list) == nullptr;
}
