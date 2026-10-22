
#include <cstdlib>
#include "queue.h"
using namespace std;

#define CHECK(x) do { if (!(x)) abort(); } while (false)

int main() {
    Queue queue;

    CHECK(queue.empty());

    queue.insert(10);
    CHECK(!queue.empty());
    CHECK(queue.get() == 10);

    queue.insert(20);
    queue.insert(30);
    CHECK(queue.get() == 10);

    queue.remove();
    CHECK(queue.get() == 20);

    queue.remove();
    CHECK(queue.get() == 30);

    
    queue.remove();
    CHECK(queue.empty());

    queue.insert(40);
    CHECK(queue.get() == 40);

    queue.remove();
    CHECK(queue.empty());
}
