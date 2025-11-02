#include "stack.h"
#include "list.h"
#include <cassert>

struct Stack {
    List* list;
};

Stack* stack_create() {
    auto* st = new Stack;
    st->list = list_create();
    return st;
}

void stack_delete(Stack* stack) {
    if (!stack) return;
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack* stack, Data data) {
    assert(stack);
    list_insert(stack->list, data);
}

Data stack_get(const Stack* stack) {
    assert(stack);
    auto* first = list_first(const_cast<List*>(stack->list));
    assert(first && "stack_get on empty stack");
    return list_item_data(first);
}

void stack_pop(Stack* stack) {
    assert(stack);
    auto* first = list_first(stack->list);
    assert(first && "stack_pop on empty stack");
    list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack) {
    if (!stack) return true;
    return list_first(const_cast<List*>(stack->list)) == nullptr;
}
