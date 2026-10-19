#include <iostream>
#include <cassert>
#include "../queue.h"

int main() {
    Queue q;
    assert(q.empty() == true);

    q.insert(100);
    q.insert(200);
    assert(q.get() == 100);

    q.remove();
    assert(q.get() == 200);

    q.remove();
    assert(q.empty() == true);

    std::cout << "LibraryCPP Queue internal test passed!\n";
    return 0;
}
