#include "stack.h"
#include "vector.h"

struct Stack 
{
    Vector* v;
};

Stack* stack_create() 
{
    Stack* s = new Stack;
    s->v = vector_create();
    return s;
}

void stack_delete(Stack* s) 
{
    vector_delete(s->v);
    delete s;
}

void stack_push(Stack* s, Data data) 
{
    size_t n = vector_size(s->v);
    vector_resize(s->v, n + 1);
    vector_set(s->v, n, data);
}

Data stack_get(const Stack* s) 
{
    size_t n = vector_size(s->v);
    if (n == 0) 
        return 0;
    
    return vector_get(s->v, n - 1);
}

void stack_pop(Stack* s) 
{
    size_t n = vector_size(s->v);
    if (n > 0) 
        vector_resize(s->v, n - 1);
}

bool stack_empty(const Stack* s) 
{
    return vector_size(s->v) == 0;
}
