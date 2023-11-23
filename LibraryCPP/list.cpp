#include <cstddef>
#include "list.h"

struct ListItem
{
public:
    Data data;
    ListItem* Next = nullptr;

};

struct List
{
    ListItem* Head = nullptr;
    ListItem* Tail = nullptr;



};

List* list_create()
{

    return new List;
}

void list_delete(List* list)
{

    while (list->Head)
    {
        list_erase_first(list);
    }
    delete list;

}

ListItem* list_first(List* list)
{
    return list->Head;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{

    return item = item->Next;
}

ListItem* list_item_prev(ListItem* item)
{
    return NULL;
}

ListItem* list_insert(List* list, Data data)
{

    ListItem* NewNode = new ListItem;
    NewNode->data = data;
    NewNode->Next = list->Head;

    if (!list->Head)
    {
        list->Tail = NewNode;
    }
    list->Head = NewNode;
    return NewNode;

}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (!item)
    {
        return nullptr;
    }
    ListItem* NewNode = new ListItem;
    NewNode->data = data;
    NewNode->Next = item->Next;
    item->Next = NewNode;
    if (item == list->Tail)
    {
        list->Tail = NewNode;
    }
    return NewNode;

}

ListItem* list_erase_first(List* list)
{             ////Удаление посмотреть, тест работает неккоректно
    if (list->Head)
    {
        ListItem* TempItem = new ListItem;
        TempItem = list->Head;
        list->Head = list->Head->Next;
        delete TempItem;
        return list->Head;
    }
    return nullptr;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!item || !item->Next)
    {
        return nullptr;
    }
    ListItem* item_to_delete;

    item_to_delete = item->Next;

    item->Next = item_to_delete->Next;
    if (item_to_delete == list->Tail)
    {
        list->Tail = item;
    }
    delete item_to_delete;

    return item->Next;
}