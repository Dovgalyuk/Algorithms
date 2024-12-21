#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem* prev;
};

struct List
{
    ListItem* head;
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list)
{
    // TODO: free items
    if (!list) return;
    ListItem* current = list->head;
    if (current) {
        do {
            ListItem* next = current->next;
            delete current;
            current = next;
        } while (current != list->head);
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list ? list->head : NULL;
}

Data list_item_data(const ListItem *item)
{
    return item ? item->data : (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    return item ? item->next : NULL;
}

ListItem *list_item_prev(ListItem *item)
{
    return item ? item->prev : NULL;
}

ListItem *list_insert(List *list, Data data)
{
    if (!list) return NULL;
    ListItem* new_item = new ListItem(data, nullptr, nullptr);
    if (!list->head) {
        new_item->next = new_item->prev = new_item;
        list->head=new_item
    }
    else {
        ListItem* tail = list->head->prev;
        new_item->next = list->head;
        new_item->prev = tail;
        tail->next = new_item;
        list->head->prev = new_item;
    }
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return NULL;
    ListItem* new_item = new ListItem(data, item->next, item);
    item->next->prev = new_item;
    item->next = new_item;
    return new_item
}

ListItem *list_erase_first(List *list)
{
    if (!list) return NULL;
    ListItem* head = list->head;
    if (head->next == head) {
        list->head = NULL;
    }
    else {
        ListItem* tail = head->prev;
        list->head = head->next;
        list->head->prev = tail;
        tail->next = list->head;
    }
    delete head;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list) return NULL;
    ListItem* to_delete = item->next;
    item->next = to_delete->next;
    to_delete->next->prev = item;
    if (list->head == to_delete)
        list->head = to_delete->next;
    delete to_delete;
    return item->next;
}
