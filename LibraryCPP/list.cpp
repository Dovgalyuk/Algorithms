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

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

ListItem* list_erase(List* list, ListItem* item)
{
    if (!item || !list->head) return nullptr;

    if (item->next == item) {
        list->head = nullptr;
    }
    else{
        item->prev->next = item->next;
        item->next->prev = item->prev;
        if (item == list->head){
            list->head = item->next;
        }
    }

    delete item;
    return list->head;
}

void list_delete(List* list)
{
    if (!list->head) {
        delete list;
        return;
    }

    ListItem* current = list->head;
    do {
        ListItem* next = current->next;
        delete current;
        current = next;
    } while (current != list->head);

    delete list;
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

ListItem* list_item_prev(ListItem* item)
{
    return item->prev;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* item = new ListItem;
    item->data = data;

    if (!list->head){
        list->head = item;
        item->next = item;
        item->prev = item;
    }
    else{
        item->prev = list->head->prev;
        item->next = list->head;
        list->head->prev->next = item;
        list->head->prev = item;
    }
    list->head = item;

    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;

    if (!list->head){
        return list_insert(list, data);
    }
    else
    {
        new_item->next = item->next;
        new_item->prev = item;
        item->next->prev = new_item;
        item->next = new_item;
    }

    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (!list->head) return nullptr;

    ListItem* delete_item = list->head;
    if (delete_item->next == delete_item) {
        list->head = nullptr;
    }
    else{
        ListItem* new_head = delete_item->next;
        delete_item->prev->next = new_head;
        new_head->prev = delete_item->prev;
        list->head = new_head;
    }

    delete delete_item;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!item || !list->head) return nullptr;
    return list_erase(list, item->next);
}
