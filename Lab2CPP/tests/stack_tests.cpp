#include "stack.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#define CHECK(cond)                                                     \
    do {                                                                \
        if (!(cond)) {                                                  \
            std::cerr << "FAIL: " #cond " at " __FILE__ ":"             \
                      << __LINE__ << "\n";                              \
            std::exit(1);                                               \
        }                                                               \
    } while (0)

static void testCreateEmpty() {
    Stack *s = stack_create();
    CHECK(stack_empty(s));
    stack_delete(&s);
    CHECK(s == nullptr);
    std::cout << "testCreateEmpty OK\n";
}

static void testPushGetPop() {
    Stack *s = stack_create();
    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);

    CHECK(!stack_empty(s));
    CHECK(stack_get(s) == 3);
    stack_pop(s);
    CHECK(stack_get(s) == 2);
    stack_pop(s);
    CHECK(stack_get(s) == 1);
    stack_pop(s);
    CHECK(stack_empty(s));

    stack_delete(&s);
    std::cout << "testPushGetPop OK\n";
}

static void testManyPushes() {
    Stack *s = stack_create();
    const int N = 10000;
    for (int i = 0; i < N; ++i) {
        stack_push(s, i);
    }
    for (int i = N - 1; i >= 0; --i) {
        CHECK(stack_get(s) == i);
        stack_pop(s);
    }
    CHECK(stack_empty(s));
    stack_delete(&s);
    std::cout << "testManyPushes OK\n";
}

static void testEmptyThrows() {
    Stack *s = stack_create();

    bool thrown = false;
    try {
        stack_get(s);
    } catch (const std::underflow_error &) {
        thrown = true;
    }
    CHECK(thrown);

    thrown = false;
    try {
        stack_pop(s);
    } catch (const std::underflow_error &) {
        thrown = true;
    }
    CHECK(thrown);

    stack_delete(&s);
    std::cout << "testEmptyThrows OK\n";
}

static void testDeleteNull() {
    Stack *s = nullptr;
    stack_delete(&s);
    stack_delete(nullptr);
    CHECK(stack_empty(nullptr));
    std::cout << "testDeleteNull OK\n";
}

int main() {
    testCreateEmpty();
    testPushGetPop();
    testManyPushes();
    testEmptyThrows();
    testDeleteNull();
    std::cout << "All stack tests passed\n";
    return 0;
}