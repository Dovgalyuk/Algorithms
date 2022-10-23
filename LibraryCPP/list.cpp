#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;

    ListItem(Data data, ListItem* next) {
        this->data = data;
        this->next = next;
    }
};

struct List
{
    ListItem* head = NULL;
    ListItem* last = NULL;

    ~List() {
        ListItem* current = this->head;
        while (current) {
            ListItem* next = current->next;
            delete current;
            current = next;
        }
    }
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
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

ListItem *list_item_prev(ListItem *item)
{
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* new_item = new ListItem(data, NULL);
    
    new_item->next = list->head;

    if(!list->head) list->last = new_item;

    return list->head = new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* new_item = new ListItem(data, item->next);

    if (item == list->last) list->last = new_item;
    
    return item->next = new_item;
}

ListItem *list_erase(List *list, ListItem *item)
{
    //Case when we need to delete head item. 
    //We don't need to know about previous.
    if (item == list->head) {
        ListItem* next = list_item_next(item);
        delete item;
        return list->head = next;
    }
    
    //TODO: the other cases should be in the implementation of a doubly linked list

    return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item->next) {
        ListItem* next = item->next->next;
        delete item->next;
        return item->next = next;
    }
    
    return 0;
}

ListItem* list_last(List* list) {
    return list->last;
}
