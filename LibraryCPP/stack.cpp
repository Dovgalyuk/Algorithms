#include "stack.h"
#include "list.h"

struct Stack {
    List* list = list_create();
};

Stack* stack_create() {
    return new Stack;
}

void stack_delete(Stack* stack) {
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack* stack, Data data) {
    list_insert(stack->list, data);
}

Data stack_get(const Stack* stack) {
    ListItem* first = list_first(stack->list);
    return first ? list_item_data(first) : 0;
}

void stack_pop(Stack* stack) {
    list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack) {
    return list_first(stack->list) == nullptr;
}