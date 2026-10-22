#include <cassert>

#include "list.h"

int main() {
    List list;

    assert(list.first() == nullptr);

    ListItem* first = list.insert_after(list.dummy, 10);
    assert(list.first() == first);
    assert(first->data == 10);
    assert(first->next == list.dummy);

    ListItem* second = list.insert_after(first, 20);
    ListItem* middle = list.insert_after(first, 15);
    assert(list.first() == first);
    assert(first->next == middle);
    assert(middle->next == second);
    assert(second->next == list.dummy);

    list.erase_after(first);
    assert(first->next == second);
    assert(second->data == 20);

    list.erase_after(list.dummy);
    assert(list.first() == second);

    list.erase_after(list.dummy);
    assert(list.first() == nullptr);
    assert(list.dummy->next == list.dummy);

  
    list.erase_after(list.dummy);
    assert(list.first() == nullptr);
}
