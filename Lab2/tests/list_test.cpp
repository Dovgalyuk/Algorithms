#include "list.h"

int main() {
    List<char> l;
    l.insert('C');
    l.insert('B');
    l.insert('A');

    auto i = l.first();
    if (!i || i->data() != 'A') return 1;
    if (!i->next() || i->next()->data() != 'B') return 1;
    if (!i->next()->next() || i->next()->next()->data() != 'C') return 1;
    if (i->next()->next()->next() != nullptr) return 1;

    l.erase_first();
    if (l.first()->data() != 'B') return 1;

    return 0;
}