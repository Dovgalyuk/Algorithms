#include <iostream>
#include "stack.h"

using namespace std;

#define CHECK(cond, msg)                         \
    if (!(cond))                                 \
    {                                            \
        cout << "FAILED: " << msg << "\n";  \
        stack_delete(stack);                     \
        return 1;                                \
    }

int main()
{
    Stack *stack = stack_create();

    CHECK(stack_empty(stack), "new stack is not empty");

    stack_push(stack, 1);
    CHECK(!stack_empty(stack), "stack is empty after push");
    CHECK(stack_get(stack) == 1, "top after push(1)");
    stack_push(stack, 2);
    stack_push(stack, 3);
    CHECK(stack_get(stack) == 3, "top after push(3)");

    stack_pop(stack);
    CHECK(stack_get(stack) == 2, "top after first pop");
    stack_pop(stack);
    CHECK(stack_get(stack) == 1, "top after second pop");
    stack_pop(stack);
    CHECK(stack_empty(stack), "stack is not empty after popping all");

    stack_pop(stack);
    CHECK(stack_empty(stack), "pop on empty stack");

    stack_push(stack, -5);
    CHECK(stack_get(stack) == -5, "push after empty");
    stack_pop(stack);

    const Data N = 1000000;
    for (Data i = 0; i < N; ++i)
        stack_push(stack, i);
    for (Data i = N - 1; i >= 0; --i)
    {
        CHECK(stack_get(stack) == i, "wrong order on many elements");
        stack_pop(stack);
    }
    CHECK(stack_empty(stack), "stack is not empty after many pops");

    stack_delete(stack);
    cout << "stack: OK\n";
    return 0;
}