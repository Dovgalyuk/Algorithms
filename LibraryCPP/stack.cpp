#include "stack.h"
#include "list.h"

struct Stack {
    List* list;
};

Stack* stack_create() {
    Stack* s = new Stack;
    s->list = list_create();
    return s;
}

void stack_delete(Stack* stack) {
    if (!stack)
        return;

    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack* stack, Data data) {
    list_insert(stack->list, data);
}

Data stack_get(const Stack* stack) {
    ListItem* first = list_first(const_cast<List*>(stack->list));
    return list_item_data(first);
}

void stack_pop(Stack* stack) {
    list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack) {
    return list_first(const_cast<List*>(stack->list)) == nullptr;
}