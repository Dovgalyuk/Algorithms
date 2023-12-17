#include <cstddef>
#include <iostream>
#include "list.h"
#include "stack.h"
using namespace std;

struct Stack
{
    List* list;
};

Stack* stack_create()
{
    Stack* stack = new Stack;
    stack->list = list_create();
    return stack;
}

void stack_delete(Stack* stack)
{
    list_erase_first(stack->list);
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack* stack, Data newData)
{
    ListItem* newItem = list_insert(stack->list, newData);
    (void)newItem;
}

Data stack_get(const Stack* stack)
{
    if (stack_empty(stack)) {
        cout << "Empty\n";
    }
    const ListItem* item = list_first(stack->list);
    return list_item_data(item);
}

void stack_pop(Stack* stack)
{
    if (list_first(stack->list) == nullptr)
    {
        cout << "Empty stack\n";
        return;
    }
    list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack)
{
    return list_first(stack->list) == nullptr;
}
