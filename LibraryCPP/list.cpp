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
    if (!list->ListHead) throw "You tryed to use insert after to empty list";
    else if (list->ListHead->pointerNext == nullptr) {
        ListItem* add_item = new ListItem(data, nullptr, item);
        list->ListTail = add_item;
        return list->ListHead->pointerNext = new ListItem(data, nullptr, item);
    }
    else {
        ListItem* add_item = new ListItem(data, item->pointerNext, item);
        item->pointerNext = add_item;
        (item == list->ListTail) ? list->ListTail = add_item : add_item->pointerNext->pointerPrev = add_item;
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
    if (!list->ListHead) throw "You tryed to use function erase next to empty list";
    else if (item == list->ListHead) {
        if (item->pointerNext != list_last(list)) {

            item->pointerNext = item->pointerNext->pointerNext;
            delete item->pointerNext->pointerPrev;
            item->pointerNext->pointerPrev = list->ListHead;
            return item->pointerNext;
        }
        else {
            throw "Function won't return next to the item element, because after delete item is last element";
            /*delete item->pointerNext;
            item->pointerNext = nullptr;
            list->ListTail = item;
            return item;*/
        }
        
    }
    else if (item == list->ListTail) {
        throw "You tryed to use function erase next to last element";
    }
    else {
        ListItem* del_item = item->pointerNext;
        if (del_item != list_last(list)) {
            item->pointerNext = del_item->pointerNext;
            del_item->pointerNext->pointerPrev = item;
            delete del_item;
            return item->pointerNext;
        }
        else {
            throw "Function won't return next to the item element, because after delete item is last element";
            /*item->pointerNext = nullptr;
            list->ListTail = item;
            delete del_item;
            return list->ListTail;*/
        }
        
    }
}