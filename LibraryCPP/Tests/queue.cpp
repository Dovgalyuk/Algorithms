#include <cassert>

#include "queue.h"

int main() {
    Queue queue;

    assert(queue.empty());

    queue.insert(10);
    assert(!queue.empty());
    assert(queue.get() == 10);

    queue.insert(20);
    queue.insert(30);
    assert(queue.get() == 10);

    queue.remove();
    assert(queue.get() == 20);

    queue.remove();
    assert(queue.get() == 30);

    // Removing the last item must reset the tail so the queue can be reused.
    queue.remove();
    assert(queue.empty());
    queue.insert(40);
    assert(queue.get() == 40);

    queue.remove();
    assert(queue.empty());
}
