#include <iostream>

#include "vector.h"
#include "stack.h"

using namespace std;

int main()
{
    Vector *values = vector_create();
    bool valid = vector_size(values) == 0;
    vector_resize(values, 20);
    for (size_t i = 0; i < 20; ++i)
    {
        valid = valid && vector_get(values, i) == 0;
        vector_set(values, i, static_cast<int>(i + 1));
    }

    vector_resize(values, 5);
    vector_resize(values, 30);
    for (size_t i = 0; i < 30; ++i)
        valid = valid && vector_get(values, i) == (i < 5 ? static_cast<int>(i + 1) : 0);

    vector_resize(values, 0);
    vector_resize(values, 1);
    valid = valid && vector_size(values) == 1 && vector_get(values, 0) == 0;
    vector_delete(values);

    Stack *values_stack = stack_create();
    valid = valid && stack_empty(values_stack);
    stack_pop(values_stack);
    for (int i = 0; i < 10000; ++i)
        stack_push(values_stack, i);

    for (int i = 9999; i >= 0; --i)
    {
        valid = valid && !stack_empty(values_stack) && stack_get(values_stack) == i;
        stack_pop(values_stack);
    }
    valid = valid && stack_empty(values_stack);
    stack_push(values_stack, 7);
    valid = valid && stack_get(values_stack) == 7;
    stack_delete(values_stack);

    if (!valid)
    {
        cerr << "Container test failed\n";
        return 1;
    }
    return 0;
}
