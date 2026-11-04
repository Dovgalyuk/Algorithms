#include <cstddef>
#include "list.h"

struct ListItem
{
    Data value;
    ListItem* next;
    bool isDummy = false;
};

struct List
{
    ListItem* head;

    List() {
        head = new ListItem{Data(), nullptr, true};
        head->next = head;
    }

    ~List() {
        if (head == nullptr){
            return;
        }

        ListItem* current = head->next;

        while(current != head){
            ListItem* temp = current;
            current = current->next;
            delete temp;
        }

        delete head;
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
    if(list->head->next == list->head){
        return nullptr;
    }
    return list->head->next;
}

ListItem *list_last(List *list)
{
    if (list->head->next == list->head){
        return nullptr;
    }

    ListItem* current = list->head->next;

    while(current->next != list->head){
        current = current->next;
    }
    return current;
}

Data list_item_data(const ListItem *item)
{
    if (item == nullptr){
        return Data();
    }

    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    if(item == nullptr){
        return nullptr;
    }

    if (item->next->isDummy) {
        return nullptr;
    }

    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
   ListItem* item = new ListItem{data, list->head->next};
   list->head->next = item;

   return item;

}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list == nullptr){
        return nullptr;
    }

    if (item == nullptr){
        return list_insert(list, data);
    }

    ListItem* newItem = new ListItem{data, item->next};    

    item->next = newItem;

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list->head->next == list->head){
        return nullptr;
    }

    ListItem* removed = list->head->next;

    list->head->next = removed->next;

    delete removed;

    return list_first(list);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr) {
        return list_erase_first(list);
    }

    if (item->next == list->head){
        return nullptr;
    }
    
    ListItem* removed = item->next;
    item->next = removed->next;
    
    delete removed;

    if(item->next == list->head) {
        return nullptr;
    }

    return item->next;
}
