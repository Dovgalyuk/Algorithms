//Односвязный список устроен так, что каждый элемент указывает на следующий

#include <cstddef>
#include "list.h"

//Структура описывает элемент односвязного списка
struct ListItem
{
    //Указатель на следующий элемент
    ListItem* pNext;
    //Данные, которые хранятся в элементе
    Data data;
};

//Структура описывает односвязный список
struct List
{
    //Указатель на первый элемент
    ListItem* head;
};

//Функция создаёт список
List* list_create()
{
    //Создаём новый список
    List* list = new List;
    //Присваиваем первому элементу nullptr
    list->head = nullptr;
    //Возвращаем этот список
    return list;
}

//Функция удаляет список
void list_delete(List* list)
{
    //Пока есть элементы после первого выполняем цикл
    while (list_item_next(list->head))
    {
        //Удаляем элемент после первого
        list_erase_next(list, list->head);
    }
    //Удаляем первый элемент
    delete list->head;
    //Удаляем список
    delete list;

}

//Функция возвращает первый элемент списка
ListItem* list_first(List* list)
{
    //Проверяем есть ли первый элемент, если есть возвращаем его, иначе NULL
    if (list->head)
        return list->head;
    else
        return NULL;

}

//Функция возвращает данные, которые хранятся в указанном элементе
Data list_item_data(const ListItem* item)
{
    //Проверяем есть ли элемент, если есть возвращаем его значение, иначе NULL
    if (item)
        return item->data;
    else
        return NULL;
}

//Функция возвращает элемент списка, который следует за указанным
ListItem* list_item_next(ListItem* item)
{
    //Проверяем есть ли элемент, если есть возвращаем ссылку на следующий элемент, иначе NULL
    if (item)
        return item->pNext;
    else
        return NULL;
}

//Функция не подходит для односвязного списка
ListItem* list_item_prev(ListItem* item)
{
    return NULL;
}

//Функция вставляет новый элемент в начало списка
ListItem* list_insert(List* list, Data data)
{
    //Создаём новый элемент списка
    ListItem* a = new ListItem;
    a->data = data;
    //Указываем ссылку на первый элемент списка в новом элементе
    a->pNext = list_first(list);
    //У списка переприсваиваем первый элемент списка на новый
    list->head = a;
    return a;
}

//Функция вставляет новый элемент в список после указанного элемента
ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    //Создаём новый элемент списка
    ListItem* a = new ListItem;
    a->data = data;
    //Указываем ссылку на следующий за указанным элемент списка в новом элементе
    a->pNext = item->pNext;
    //У списка переприсваиваем указанный элемент списка на новый
    item->pNext = a;
    return a;
}

//Функция не подходит для односвязного списка
ListItem* list_erase(List* list, ListItem* item)
{
    return NULL;
}

//Функция удаляет элемент списка после указанного
ListItem* list_erase_next(List* list, ListItem* item)
{
    //Создаём новый элемент списка (Используем для удаления данных)
    ListItem* erase = nullptr;
    //Проверяем существует ли необходисый нам элемент
    if (list_item_next(item))
    {
        //Присваиваем erase элемент, который нам нужно удалить
        erase = item->pNext;
        //Присваиваем ссылку на следующий за указанным элемент списка указанному элементу
        item->pNext = list_item_next(list_item_next(item));
        delete erase;
        return item;
    }
    else
        return NULL;
}
