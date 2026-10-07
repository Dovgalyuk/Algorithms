#include <memory>
#include <stdexcept>
#include "list.h"
#include "stack.h"

void check(bool condition)
{
    if (!condition)
        throw std::runtime_error("Container check failed");
}

int main()
{
    std::unique_ptr<List, decltype(&list_delete)> list(list_create(), list_delete);
    check(!list_first(list.get()) && !list_last(list.get()));
    check(!list_erase_first(list.get()));
    ListItem *first = list_insert_after(list.get(), nullptr, 1);
    ListItem *last = list_insert_after(list.get(), first, 3);
    ListItem *middle = list_insert_after(list.get(), first, 2);
    check(list_first(list.get()) == first && list_last(list.get()) == last);
    check(list_item_next(first) == middle && list_item_next(middle) == last);
    check(list_erase_next(list.get(), first) == last);
    check(list_erase_next(list.get(), first) == nullptr);
    check(list_last(list.get()) == first);
    check(list_erase_next(list.get(), nullptr) == nullptr);
    check(!list_first(list.get()) && !list_last(list.get()));
    last = list_insert(list.get(), 4);
    check(list_first(list.get()) == last && list_last(list.get()) == last);
    // Destruction must free a nonempty list without recursive traversal.
    for (int i = 0; i < 100000; ++i)
        list_insert(list.get(), i);

    std::unique_ptr<Stack, decltype(&stack_delete)> stack(stack_create(), stack_delete);
    check(stack_empty(stack.get()));
    for (int i = 0; i < 100000; ++i)
        stack_push(stack.get(), i);
    for (int i = 99999; i >= 0; --i)
    {
        check(stack_get(stack.get()) == i);
        stack_pop(stack.get());
    }
    check(stack_empty(stack.get()));
    bool get_failed = false;
    bool pop_failed = false;
    try { stack_get(stack.get()); }
    catch (const std::out_of_range &) { get_failed = true; }
    try { stack_pop(stack.get()); }
    catch (const std::out_of_range &) { pop_failed = true; }
    check(get_failed && pop_failed);
    stack_push(stack.get(), 42);
    check(stack_get(stack.get()) == 42);
}
