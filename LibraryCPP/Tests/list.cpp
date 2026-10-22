
#include <cstdlib>
#include "list.h"
using namespace std;

#define CHECK(condition) \
    do { \
        if (!(condition)) { \
            abort(); \
        } \
    } while (false)

int main() {
    List list;

    CHECK(list.first() == nullptr);

    ListItem* first = list.insert_after(list.dummy, 10);
    CHECK(list.first() == first);
    CHECK(first->data == 10);
    CHECK(first->next == list.dummy);

    ListItem* second = list.insert_after(first, 20);
    ListItem* middle = list.insert_after(first, 15);

    CHECK(list.first() == first);
    CHECK(first->next == middle);
    CHECK(middle->next == second);
    CHECK(second->next == list.dummy);

    list.erase_after(first);
    CHECK(first->next == second);
    CHECK(second->data == 20);

    list.erase_after(list.dummy);
    CHECK(list.first() == second);

    list.erase_after(list.dummy);
    CHECK(list.first() == nullptr);
    CHECK(list.dummy->next == list.dummy);

    list.erase_after(list.dummy);
    CHECK(list.first() == nullptr);
}
