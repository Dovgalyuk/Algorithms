#include <cstddef>
#include <stdexcept>
#include "list.h"

struct ListItem
{
    Data data{};
    ListItem* prev = nullptr;
    ListItem* next = nullptr;
    bool sentinel = false;
};

struct List
{
    ListItem dummy;

    List() {
        dummy.sentinel = true;
        dummy.next = &dummy;
        dummy.prev = &dummy;
    }
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    // TODO: free items
    if (!list) return;
    while (list_first(list)) {
        list_erase_first(list);
    }
    delete list;
}

ListItem *list_first(List *list)
{
    if (!list || list->dummy.next == &list->dummy) return nullptr;
    return list->dummy.next;
}

ListItem *list_last(List *list)
{
    if (!list || list->dummy.prev == &list->dummy) return nullptr;
    return list->dummy.prev;return NULL;
}

Data list_item_data(const ListItem *item)
{
    if (!item || item->sentinel) throw std::out_of_range("Invalid list item");
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item || item->sentinel || item->next->sentinel) return nullptr;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item || item->sentinel || item->prev->sentinel) return nullptr;
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) throw std::invalid_argument("List is null");
    ListItem* left = item ? item : &list->dummy;
    ListItem* right = left->next;
    ListItem* node = new ListItem{data, left, right, false};
    left->next = node;
    right->prev = node;
    return node;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list) throw std::invalid_argument("List is null");
    ListItem* left = item ? item : &list->dummy;
    ListItem* target = left->next;
    if (target == &list->dummy) return nullptr;
    ListItem* right = target->next;
    left->next = right;
    right->prev = left;
    delete target;
    return right == &list->dummy ? nullptr : right;
}
