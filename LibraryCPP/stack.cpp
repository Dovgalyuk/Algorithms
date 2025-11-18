#include "stack.h"
#include "vector.h"
#include <stdexcept>

struct Stack {
    Vector* vec;
};

Stack* stack_create() {
    Stack* s = new Stack;
    s->vec = vector_create();
    return s;
}

void stack_delete(Stack* s) {
    vector_delete(s->vec);
    delete s;
}

void stack_push(Stack* s, Data data) {
    size_t sz = vector_size(s->vec);
    vector_resize(s->vec, sz+1);
    vector_set(s->vec, sz, data);
}

Data stack_get(const Stack* s) {
    size_t sz = vector_size(s->vec);
    if(sz == 0) throw std::runtime_error("stack_get on empty stack");
    return vector_get(s->vec, sz-1);
}

void stack_pop(Stack* s) {
    size_t sz = vector_size(s->vec);
    if(sz == 0) throw std::runtime_error("stack_pop on empty stack");
    vector_resize(s->vec, sz-1);
}

bool stack_empty(const Stack* s) {
    return vector_size(s->vec) == 0;
}
