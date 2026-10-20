#include "list.h"

//узел
struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *head;
    ListItem *tail;
};

List *list_create()
{
    List *list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List *list)
{
    ListItem *item = list->head;
    while (item != nullptr)
    {
        ListItem *next = item->next;
        delete item;
        item = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

ListItem *list_last(List *list)
{
    return list->tail;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

// cписок односвязный, предыдущий элемент получить нельзя
ListItem *list_item_prev(ListItem *item)
{
    (void)item;
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *new_item = new ListItem;
    new_item->data = data;

    if (item == nullptr){
        new_item->next = list->head;
        list->head = new_item;
    }
    else{
        new_item->next = item->next;
        item->next = new_item;
    }

    if (new_item->next == nullptr){
        list->tail = new_item;
    }
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *target = (item == nullptr) ? list->head : item->next;
    if (target == nullptr){
        return nullptr;
    }
    ListItem *next = target->next;
    if (item == nullptr){
        list->head = next;
    }
    else{
        item->next = next;
    }

    if (target == list->tail){
        list->tail = item;
    }

    delete target;
    return next;
}
