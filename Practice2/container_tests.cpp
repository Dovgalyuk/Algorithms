#include "list.h"
#include "stack.h"
#include <iostream>
#include <stdexcept>

static bool check(bool condition, const char *message)
{
    if (!condition)
        std::cerr << "FAILED: " << message << '\n';
    return condition;
}

int main()
{
    List list;
    if (!check(list.first() == nullptr && list.last() == nullptr, "empty list")) return 1;

    List::Item *one = list.insert(1);
    List::Item *two = list.insert_after(one, 2);
    List::Item *three = list.insert_after(two, 3);
    if (!check(list.first()->data() == 1 && list.last()->data() == 3, "insert and last")) return 1;
    if (!check(one->next() == two && two->prev() == one && two->next() == three && three->prev() == two,
               "next and prev links")) return 1;

    list.erase_next(one);
    if (!check(one->next() == three && three->prev() == one, "erase middle item")) return 1;
    list.erase_next(nullptr);
    if (!check(list.first() == three && list.last() == three && three->prev() == nullptr,
               "erase first item through erase_next(nullptr)")) return 1;
    list.erase_first();
    if (!check(list.first() == nullptr && list.last() == nullptr, "erase last item")) return 1;

    list.insert(3);
    list.insert(2);
    list.insert(1);
    List copy(list);
    if (!check(copy.first()->data() == 1 && copy.last()->data() == 3, "list copy constructor")) return 1;
    copy.erase_first();
    if (!check(list.first()->data() == 1, "list copy is independent")) return 1;
    List assigned;
    assigned = list;
    if (!check(assigned.first()->data() == 1 && assigned.last()->data() == 3, "list assignment")) return 1;

    Stack stack;
    if (!check(stack.empty(), "empty stack")) return 1;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    if (!check(stack.get() == 3, "stack push/get")) return 1;
    Stack stack_copy(stack);
    stack_copy.pop();
    if (!check(stack_copy.get() == 2 && stack.get() == 3, "stack copy is independent")) return 1;
    Stack stack_assigned;
    stack_assigned = stack;
    if (!check(stack_assigned.get() == 3, "stack assignment")) return 1;
    stack.pop();
    stack.pop();
    stack.pop();
    if (!check(stack.empty(), "pop until empty")) return 1;

    bool threw = false;
    try
    {
        (void)stack.get();
    }
    catch (const std::out_of_range &)
    {
        threw = true;
    }
    if (!check(threw, "get on empty stack throws")) return 1;

    std::cout << "Container tests passed\n";
    return 0;
}
