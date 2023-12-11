#include "stack.h"
#include "list.cpp"

struct Stack
{
    List* list;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->list = listCreate();
    return stack;
}

Stack* stack_push(Stack* stack,Data data) {
    insertMake(stack->stack, data);
}
Data stack_getStack(Stack* stack) {
    ListItem* last = list_last(stack->list);
    if (last) {
        return list_item_data(last);
    }
    else {
        return (Data)0;
    }
}
void stack_pop(Stack* stack)
{
    list_erase_last(stack->list);
}
void stack_delete(Stack* stack) {
    list_delete(stack);
}
bool stack_empty(Stack* stack) {
    return list_first(stack->list) == nullptr;
}