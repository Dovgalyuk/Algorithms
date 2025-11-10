#include "list.h"
#include <stdexcept>

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
    if (!list) return;
    
    ListItem* current = list->head;
    while (current) {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list ? list->head : nullptr;
}

Data list_item_data(const ListItem *item)
{
    if (!item) throw std::invalid_argument("Null item");
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item ? item->next : nullptr;
}

ListItem *list_item_prev(ListItem *item)
{
    return item ? item->prev : nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    if (!list) return nullptr;
    
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    new_item->prev = nullptr;
    
    if (list->head) {
        list->head->prev = new_item;
    }
    list->head = new_item;
    
    if (!list->tail) {
        list->tail = new_item;
    }
    
    list->size++;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return nullptr;
    
    if (!item) {
        return list_insert(list, data);
    }
    
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;
    
    if (item->next) {
        item->next->prev = new_item;
    }
    item->next = new_item;
    
    if (list->tail == item) {
        list->tail = new_item;
    }
    
    list->size++;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head) return nullptr;
    
    ListItem* to_delete = list->head;
    ListItem* next_item = to_delete->next;
    
    list->head = next_item;
    if (next_item) {
        next_item->prev = nullptr;
    } else {
        list->tail = nullptr;
    }
    
    delete to_delete;
    list->size--;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list || !item || !item->next) return nullptr;
    
    ListItem* to_delete = item->next;
    ListItem* next_item = to_delete->next;
    
    item->next = next_item;
    if (next_item) {
        next_item->prev = item;
    } else {
        list->tail = item;
    }
    
    delete to_delete;
    list->size--;
    return next_item;
}