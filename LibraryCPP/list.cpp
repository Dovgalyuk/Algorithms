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
    ListItem* tail;

    List() {
        head = new ListItem{Data(), nullptr, true};
        head->next = head;
        tail = nullptr;
    }

    ~List() {
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
    if(list == nullptr || list->head->next == list->head){
        return nullptr;
    }
    return list->head->next;
}

ListItem *list_last(List *list)
{
    if (list == nullptr) {
        return nullptr;
    }

    return list->tail;
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
    if (list == nullptr) {
        return nullptr;
    }

   ListItem* item = new ListItem{data, list->head->next};
   list->head->next = item;

    if (list->tail == nullptr) {
        list->tail = item;
    }

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

    if (list->tail == item) {
        list->tail = newItem;
    }

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (list == nullptr || list->head->next == list->head) {
        return nullptr;
    }

    ListItem* removed = list->head->next;

    list->head->next = removed->next;

    if (list->tail == removed) {
        list->tail = nullptr;
    }

    delete removed;

    return list_first(list);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == nullptr) {
        return nullptr;
    }

    if (item == nullptr) {
        return list_erase_first(list);
    }

    if (item->next == list->head){
        return nullptr;
    }
    
    ListItem* removed = item->next;
    item->next = removed->next;

    if (list->tail == removed) {
        list->tail = item;
    }
    
    delete removed;

    if(item->next == list->head) {
        return nullptr;
    }

    return item->next;
}
