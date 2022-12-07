#include <cstddef>
#include<iostream>
#include "list.h"

struct ListItem//Элемент списка
{
    Data data;//данные
    ListItem* next, * prev;//следующий и предыдущий элемент

    ListItem(Data data = NULL, ListItem* next = nullptr, ListItem* prev = nullptr) {
        this->data = data;
        this->next = next;
        this->prev = prev;

    }
};

struct List//Список
{
    ListItem* Head, * Tail;//"Голова" и "Хвост"

    List() {
        this->Head = nullptr;
        this->Tail = nullptr;
    }
};

List* list_create()//Создать список
{
    return new List;
}

void list_delete(List* list)//Удалить список
{
    // TODO: free items
    delete list;
}

ListItem* list_first(List* list)//Возвращает первый элемент из списка
{
    return list->Head;
}

Data list_item_data(const ListItem* item)//Возвращает данные из элемента списка
{
    if (item != nullptr) return item->data;
    else return NULL;
}

ListItem* list_item_next(ListItem* item)// Возвращает элемент списка, следующий за указанным
{
    return item->next;
}

ListItem* list_item_prev(ListItem* item)// Возвращает предыдущий элемент для указанного элемента.
{
    return item->prev;
}

ListItem* list_insert(List* list, Data data)// Вставляет новый элемент списка в начало
{
    if (list->Head == nullptr) {//Если список пустой, то в список добавляем элемент,который будет и головой и хвостом
        return list->Head = list->Tail = new ListItem(data);
    }
    else {
        ListItem* elem = new ListItem(data, list->Head);//создаем элемент вначале списка
        list->Head->prev = elem;//Передаем голове указатель на предыдущий элемент, который создали
        list->Head = elem;//Задаем созданный элемент, как голову
        return list->Head;//Возвращаем первый элемент списка
    }
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)// Вставляет новый элемент списка после указанного элемента
{
    if (list->Head == nullptr) {//Если список пуст
        std::cout << "error";
    }
    else {
        ListItem* elem = new ListItem(data, item->next, item);
        item->next = elem;

        if (item != list->Tail) {
            elem->next->prev = elem;
        }
        else {
            list->Tail = elem;
        }
        return elem;
    }
    
}


ListItem* list_erase(List* list, ListItem* item)
// Удаляет указанный элемент списка. Возвращает следующий элемент
{
    if (list->Head == nullptr)//Если список пуст
    {
        std::cout << "Список пуст";
    }

    else if (list->Head == item && list->Tail == item)//если удаляемый элемент - это и голова и хвост
    {
        delete item;
        return list->Head = list->Tail = nullptr;
    }

    else if (list->Head == item) //если удаляемый элемент - это голова списка
    {
        list->Head = item->next;
        list->Head->prev = nullptr;
        delete item;
        return list->Head;
    }

    else if (list->Tail == item)//если удаляемый элемент - это хвост списка
    {
        list->Tail = item->prev;
        list->Tail->next = nullptr;
        delete item;
        return list->Tail;
    }
        
    else 
    {
        ListItem* elem = item->next;
        item->prev->next = elem;
        elem->prev = item->prev;
        delete item;
        return elem;
    }
}


ListItem* list_erase_next(List* list, ListItem* item)// Удаляет элемент списка, следующий за указанным.
// Возвращает указатель на элемент рядом с удаленным.
{

    if (list->Tail == item) //если элемент равен хвосту,то следующий элемент пустой
    {
        std::cout << "Ошибка. Следующий элемент пустой";
    }

    else if (list->Head == nullptr)//Если список пуст
    {
        std::cout << "Ошибка.Список пуст";
    }
   
    else {
        return list_erase(list, item->next);
    }
}
