#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include "queue.h"

using namespace std;

#define CHECK(condition) do { if (!(condition)) { cerr << "Check failed at line " << __LINE__ << '\n'; abort(); } } while (false)

int main() {
    Queue* queue = queue_create();
    CHECK(queue_empty(queue));
    queue_remove(queue);
    CHECK(queue_empty(queue));
    bool caught = false;
    try { queue_get(queue); } catch (const out_of_range&) { caught = true; }
    CHECK(caught);

    queue_insert(queue, 10);
    queue_insert(queue, 20);
    queue_insert(queue, 30);
    for (int expected : {10, 20, 30}) {
        CHECK(!queue_empty(queue));
        CHECK(queue_get(queue) == expected);
        CHECK(queue_get(queue) == expected);
        queue_remove(queue);
    }
    CHECK(queue_empty(queue));
    queue_insert(queue, 40);
    CHECK(queue_get(queue) == 40);
    queue_remove(queue);
    CHECK(queue_empty(queue));
    for (int value : {numeric_limits<int>::min(), 0, numeric_limits<int>::max()}) {
        queue_insert(queue, value);
        CHECK(queue_get(queue) == value);
        queue_remove(queue);
    }
    for (int i = 0; i < 100000; ++i) queue_insert(queue, i);
    for (int i = 0; i < 50000; ++i) {
        CHECK(queue_get(queue) == i);
        queue_remove(queue);
    }
    for (int i = 100000; i < 150000; ++i) queue_insert(queue, i);
    for (int i = 50000; i < 150000; ++i) {
        CHECK(queue_get(queue) == i);
        queue_remove(queue);
    }
    CHECK(queue_empty(queue));
    queue_remove(queue);
    for (int i = 0; i < 10000; ++i) queue_insert(queue, i);
    queue_delete(queue);
    cout << "Queue edge cases passed\n";
}
