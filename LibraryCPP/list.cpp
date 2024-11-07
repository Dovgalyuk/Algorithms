#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head;
    ListItem* tail;
    size_t size;
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
    return list;
}

void list_delete(List *list)
{
    // TODO: free items
    ListItem* current = list->head;
    while (current != nullptr)
    {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    list->head = new_item;
    list->size++;
    return new_item;
}

ListItem* list_insert_end(List* list, Data data) 
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = nullptr;

    if (list->head == nullptr)
    {
        list->head = new_item;
        list->tail = new_item;
    }
    else
    {
        list->tail->next = new_item;
        list->tail = new_item; 
    }
    list->size++;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr) return nullptr;

    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;
    list->size++;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (!list) {
        return nullptr; 
    }
    if (list->head == nullptr) { 
        return nullptr; 
    }

    ListItem* to_delete = list->head; 

    list->head = to_delete->next;

    list->size--;

    delete to_delete;

    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr || item->next == nullptr) return nullptr;

    ListItem* to_delete = item->next;
    item->next = to_delete->next;
    list->size--;

    delete to_delete;
    return item->next;
}
