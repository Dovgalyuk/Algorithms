#include <cstddef>
#include <iostream>
#include "list.h"
#include "stack.h"
using namespace std;

struct List
{
    ListItem* begin;
};

struct ListItem
{
    Data data;
    ListItem* next;
};

List* list_create()
{
    List* list = new List;
    list->begin = nullptr;
    return list;
}

void list_delete(List* list)
{
    ListItem* current = list->begin;
    while (current != nullptr)
    {
        ListItem* temp = current->next;
        delete current;
        current = temp;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->begin;
}

Data list_item_data(const ListItem* item)
{

    if (item == nullptr) {
        cout << "Empty";
        return Data();
    }
    /*cout << "\nFirst item = " << item->data << endl;*/
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

ListItem* list_item_prev(ListItem* item)
{
    return nullptr;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->begin;
    list->begin = new_item;
    return new_item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;

    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (list->begin != nullptr) {
        ListItem* first = list->begin;
        list->begin = list->begin->next;
        delete first;
    }
    return list->begin;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item == nullptr || item->next == nullptr) {
        return nullptr; // Если элемент или следующий элемент не существуют, возвращаем nullptr
    }

    ListItem* nextItem = item->next; // Сохраняем следующий элемент
    item->next = nextItem->next; // Изменяем следующий элемент указанного элемента
    delete nextItem; // Удаляем следующий элемент

    return item->next;
}
