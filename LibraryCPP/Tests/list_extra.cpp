#include <cstdlib>
#include <iostream>
#include "list.h"

using namespace std;

#define CHECK(condition) do { if (!(condition)) { cerr << "Check failed at line " << __LINE__ << '\n'; abort(); } } while (false)

int main() {
    List* list = list_create();
    CHECK(list_first(list) == nullptr);
    CHECK(list_last(list) == nullptr);
    CHECK(list_erase_first(list) == nullptr);
    CHECK(list_item_next(nullptr) == nullptr);

    ListItem* first = list_insert_after(list, nullptr, 10);
    CHECK(list_first(list) == first);
    CHECK(list_last(list) == first);
    CHECK(list_item_data(first) == 10);
    CHECK(list_item_next(first) == nullptr);

    ListItem* last = list_insert_after(list, first, 30);
    ListItem* middle = list_insert_after(list, first, 20);
    CHECK(list_item_next(first) == middle);
    CHECK(list_item_next(middle) == last);
    CHECK(list_last(list) == last);
    CHECK(list_erase_next(list, last) == nullptr);
    CHECK(list_last(list) == last);
    CHECK(list_erase_next(list, first) == last);
    CHECK(list_item_data(list_item_next(first)) == 30);
    CHECK(list_erase_next(list, first) == nullptr);
    CHECK(list_last(list) == first);
    CHECK(list_item_next(first) == nullptr);
    CHECK(list_erase_first(list) == nullptr);
    CHECK(list_first(list) == nullptr);
    CHECK(list_last(list) == nullptr);

    last = list_insert(list, -1);
    CHECK(list_last(list) == last);
    first = list_insert(list, 0);
    CHECK(list_first(list) == first);
    CHECK(list_last(list) == last);
    CHECK(list_erase_next(list, nullptr) == last);
    CHECK(list_first(list) == last);
    CHECK(list_erase_first(list) == nullptr);
    CHECK(list_erase_first(list) == nullptr);

    for (int i = 0; i < 10000; ++i) list_insert_after(list, list_last(list), i);
    int expected = 0;
    for (ListItem* item = list_first(list); item; item = list_item_next(item))
        CHECK(list_item_data(item) == expected++);
    CHECK(expected == 10000);
    list_delete(list);
    list_delete(nullptr);
    cout << "List edge cases passed\n";
}
