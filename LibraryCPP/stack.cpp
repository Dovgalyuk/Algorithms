#include "stack.h"
#include "list.h"
#include <cassert>

struct Stack {
    List* list;
};

Stack* stack_create() {
    Stack* st = new Stack;
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
    List* lst = const_cast<List*>(stack->list);
    ListItem* first = list_first(lst);
    assert(first);
    return list_item_data(first);
}

void stack_pop(Stack* stack) {
    assert(stack);
    ListItem* first = list_first(stack->list);
    assert(first);
    list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack) {
    if (!stack) return true;
    List* lst = const_cast<List*>(stack->list);
    return list_first(lst) == nullptr;
}
