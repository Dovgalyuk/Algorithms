#include <cstddef>
#include "list.h"
using namespace std;

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* elem;
};

List* list_create()
{
    List* list = new List;
    list->elem = nullptr;
    return list;
}

void list_delete(List* list)
{
    if (list == nullptr) return;

    ListItem* current = list->elem;
    while (current != nullptr) {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    if (list == nullptr) return nullptr;
    return list->elem;
}

Data list_item_data(const ListItem* item)
{
    if (item == nullptr) return Data{};
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    if (item == nullptr) return nullptr;
    return item->next;
}

ListItem* list_item_prev(ListItem* /*item*/)
{
    return nullptr;
}

ListItem* list_insert(List* list, Data data)
{
    if (list == nullptr) return nullptr;

    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->elem;
    list->elem = newItem;
    return newItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (list == nullptr) return nullptr;

    if (item == nullptr) {
        return list_insert(list, data);
    }

    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    item->next = newItem;
    return newItem;
}

ListItem* list_erase_first(List* list)
{
    if (list == nullptr || list->elem == nullptr) return nullptr;

    ListItem* toDelete = list->elem;
    list->elem = toDelete->next;
    delete toDelete;
    return list->elem;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (list == nullptr) return nullptr;

    if (item == nullptr) {
        return list_erase_first(list);
    }

    if (item->next == nullptr) return nullptr;

    ListItem* toDelete = item->next;
    item->next = toDelete->next;
    delete toDelete;
    return item->next;
}