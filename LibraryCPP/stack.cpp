#include "stack.h"
#include "list.h"
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
    if (stack == nullptr) return;
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    if (stack == nullptr) return;
    list_insert(stack->list, data);
}

Data stack_get(const Stack* stack)
{
    if (stack == nullptr || stack_empty(stack)) return Data{};
    ListItem* first = list_first(stack->list);
    return list_item_data(first);
}

void stack_pop(Stack* stack)
{
    if (stack == nullptr || stack_empty(stack)) return;
    list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack)
{
    if (stack == nullptr) return true;
    return (list_first(stack->list) == nullptr);
}