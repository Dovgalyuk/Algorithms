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
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
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
    return item ? item->data : Data(0);
}

ListItem *list_item_next(ListItem *item)
{
    return item ? item->next : nullptr;
}

ListItem *list_item_prev(ListItem *item)
{
    // Для односвязного списка предыдущий элемент недоступен
    (void)item;
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    if (!list) return nullptr;
    
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    list->head = new_item;
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
    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head) return nullptr;
    
    ListItem* old_head = list->head;
    list->head = old_head->next;
    delete old_head;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list) return nullptr;
    
    if (!item) {
        return list_erase_first(list);
    }
    
    if (!item->next) return nullptr;
    
    ListItem* to_delete = item->next;
    item->next = to_delete->next;
    delete to_delete;
    return item->next;
}