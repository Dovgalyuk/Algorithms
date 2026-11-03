#include "vector.h"

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
    Vector *v = vector_create();
    CHECK(vector_size(v) == 0);
    vector_delete(&v);
    CHECK(v == nullptr);
    std::cout << "testCreateEmpty OK\n";
}

static void testResizeIncrease() {
    Vector *v = vector_create();
    vector_resize(v, 5);
    CHECK(vector_size(v) == 5);
    for (size_t i = 0; i < 5; ++i) {
        CHECK(vector_get(v, i) == 0);
    }
    vector_delete(&v);
    std::cout << "testResizeIncrease OK\n";
}

static void testSetGet() {
    Vector *v = vector_create();
    vector_resize(v, 3);
    vector_set(v, 0, 10);
    vector_set(v, 1, 20);
    vector_set(v, 2, 30);
    CHECK(vector_get(v, 0) == 10);
    CHECK(vector_get(v, 1) == 20);
    CHECK(vector_get(v, 2) == 30);
    vector_delete(&v);
    std::cout << "testSetGet OK\n";
}

static void testResizeDecrease() {
    Vector *v = vector_create();
    vector_resize(v, 5);
    vector_set(v, 0, 1);
    vector_set(v, 4, 5);
    vector_resize(v, 2);
    CHECK(vector_size(v) == 2);
    CHECK(vector_get(v, 0) == 1);
    vector_delete(&v);
    std::cout << "testResizeDecrease OK\n";
}

static void testManyPushBackViaResize() {
    Vector *v = vector_create();
    for (size_t i = 0; i < 1000; ++i) {
        vector_resize(v, i + 1);
        vector_set(v, i, static_cast<Data>(i));
    }
    CHECK(vector_size(v) == 1000);
    for (size_t i = 0; i < 1000; ++i) {
        CHECK(vector_get(v, i) == static_cast<Data>(i));
    }
    vector_delete(&v);
    std::cout << "testManyPushBackViaResize OK\n";
}

static void testOutOfRange() {
    Vector *v = vector_create();
    vector_resize(v, 2);

    bool thrown = false;
    try {
        vector_get(v, 5);
    } catch (const std::out_of_range &) {
        thrown = true;
    }
    CHECK(thrown);

    thrown = false;
    try {
        vector_set(v, 5, 42);
    } catch (const std::out_of_range &) {
        thrown = true;
    }
    CHECK(thrown);

    vector_delete(&v);
    std::cout << "testOutOfRange OK\n";
}

static void testDeleteNull() {
    Vector *v = nullptr;
    vector_delete(&v);
    vector_delete(nullptr);
    std::cout << "testDeleteNull OK\n";
}

int main() {
    testCreateEmpty();
    testResizeIncrease();
    testSetGet();
    testResizeDecrease();
    testManyPushBackViaResize();
    testOutOfRange();
    testDeleteNull();
    std::cout << "All vector tests passed\n";
    return 0;
}