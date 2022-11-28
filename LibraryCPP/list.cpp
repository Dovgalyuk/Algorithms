#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* pointerNext, * pointerPrev;

    ListItem(Data data, ListItem* pointerNext = nullptr, ListItem* pointerPrev = nullptr) {
        this->data = data;
        this->pointerPrev = pointerPrev;
        this->pointerNext = pointerNext;
    }
};

struct List
{
    ListItem* ListHead, *ListTail;

    List() {
        this->ListHead = nullptr;
        this->ListTail = nullptr;
    }

};

List* list_create()
{
    return new List;
}

void list_delete(List* list)
{
    ListItem* current = list->ListHead;
    while (current) {
        list->ListHead = current->pointerNext;
        delete current;
        current = list->ListHead;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->ListHead;
}

ListItem* list_last(List* list)
{
    return list->ListTail;
}

Data list_item_data(const ListItem* item)
{
    if (item != NULL) return item->data;  else return NULL;
}

ListItem* list_item_next(ListItem* item)
{
    return item->pointerNext;
}

ListItem* list_item_prev(ListItem* item)
{
    return item->pointerPrev;
}

//Вставляем элемент в начало списка
ListItem* list_insert(List* list, Data data)
{
    if (list->ListHead) return list->ListHead = new ListItem (data, list->ListHead); 
    else {
        list->ListHead = new ListItem(data);
        list->ListTail = list->ListHead;
        return list->ListHead;
    }
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (!list->ListHead)
    {
        list->ListHead = new ListItem(data);
        list->ListTail = list->ListHead;
        return list->ListHead;
    }
    else if (list->ListHead->pointerNext == nullptr) {
        ListItem* add_item = new ListItem(data, nullptr, item);
        list->ListTail = add_item;
        return list->ListHead->pointerNext = new ListItem(data, nullptr, item);
    } 
    else if (item->pointerNext == nullptr) {
        ListItem* add_item = new ListItem(data, nullptr, item);
        list->ListTail = add_item;
        return item->pointerNext = new ListItem(data, nullptr, item);
    }
    else {
        ListItem* add_item = new ListItem(data, item->pointerNext, item);
        item->pointerNext = add_item;
        add_item->pointerNext->pointerPrev = add_item;
        return add_item;
    }
}

ListItem* list_erase(List* list, ListItem* item)
{
    if (item == list_first(list)) {
        if (item == list_last(list)) {
            delete item;
            return list->ListHead = list->ListTail = nullptr;
        }
        list->ListHead = item->pointerNext;
        item->pointerNext->pointerPrev = nullptr;
        delete item;
        return list->ListHead;
    }
    else if (item == list_last(list)) {
        list->ListTail = item->pointerPrev;
        item->pointerPrev->pointerNext = nullptr;
        delete item;
        return list->ListTail;
    }
    else {
        ListItem* temp_item = item->pointerNext;
        item->pointerPrev->pointerNext = temp_item;
        item->pointerNext->pointerPrev = item->pointerPrev;
        delete item;
        return temp_item;
    }    
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item != list_last(list))
    {
        ListItem* deleted_item = item->pointerNext;
        item->pointerNext = deleted_item->pointerNext;
        deleted_item->pointerNext->pointerPrev = item;
        delete deleted_item;
        return item->pointerNext;
    }
    else {
        return list->ListHead = list->ListTail = nullptr;
    }
}