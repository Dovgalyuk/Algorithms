#include "stack.h"

int main() {
    Stack* s = stack_create();

    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);

    if (stack_get(s) != 3) return 1;
    stack_pop(s);
    if (stack_get(s) != 2) return 1;
    stack_pop(s);
    if (stack_get(s) != 1) return 1;
    stack_pop(s);

    if (!stack_empty(s)) return 1;

    stack_push(s, 42);
    if (stack_empty(s)) return 1;
    if (stack_get(s) != 42) return 1;

    stack_delete(s);
    return 0;
}
