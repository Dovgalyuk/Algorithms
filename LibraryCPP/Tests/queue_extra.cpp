#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include "queue.h"

using namespace std;

#define CHECK(condition) do { if (!(condition)) { cerr << "Check failed at line " << __LINE__ << '\n'; abort(); } } while (false)

static_assert(!is_copy_constructible<Queue>::value, "Queue must own its list");
static_assert(!is_copy_assignable<Queue>::value, "Queue must own its list");

int main() {
    Queue queue;
    CHECK(queue.empty());
    queue.remove();
    CHECK(queue.empty());
    bool caught = false;
    try { queue.get(); } catch (const out_of_range&) { caught = true; }
    CHECK(caught);

    queue.insert(10);
    queue.insert(20);
    queue.insert(30);
    for (int expected : {10, 20, 30}) {
        CHECK(!queue.empty());
        CHECK(queue.get() == expected);
        CHECK(queue.get() == expected);
        queue.remove();
    }
    CHECK(queue.empty());
    queue.insert(40);
    CHECK(queue.get() == 40);
    queue.remove();
    CHECK(queue.empty());
    for (int value : {numeric_limits<int>::min(), 0, numeric_limits<int>::max()}) {
        queue.insert(value);
        CHECK(queue.get() == value);
        queue.remove();
    }
    for (int i = 0; i < 100000; ++i) queue.insert(i);
    for (int i = 0; i < 50000; ++i) {
        CHECK(queue.get() == i);
        queue.remove();
    }
    for (int i = 100000; i < 150000; ++i) queue.insert(i);
    for (int i = 50000; i < 150000; ++i) {
        CHECK(queue.get() == i);
        queue.remove();
    }
    CHECK(queue.empty());
    queue.remove();
    for (int i = 0; i < 10000; ++i) queue.insert(i);
    cout << "Queue edge cases passed\n";
}
