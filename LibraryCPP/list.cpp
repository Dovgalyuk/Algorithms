#include <cstddef>
#include "list.h"

// Элемент списка
struct ListItem
{
    Data data;      // значение
    ListItem *next; // следующий элемент
    bool dummy;     // true только у фиктивного элемента
};

// Кольцевой односвязный список с фиктивным элементом.
// Фиктивный элемент стоит "перед" первым и "после" последнего:
// head -> 1 -> 2 -> 3 -> head
// В пустом списке head->next == head.
struct List
{
    ListItem *head; // фиктивный элемент
    ListItem *last; // последний элемент (нужен, чтобы вставка в конец была O(1))
};

List *list_create()
{
    List *list = new List;
    list->head = new ListItem;
    list->head->data = 0;
    list->head->dummy = true;
    list->head->next = list->head; // замыкаем кольцо на себя
    list->last = list->head;       // список пустой
    return list;
}

void list_delete(List *list)
{
    // удаляем все настоящие элементы
    ListItem *cur = list->head->next;
    while (cur != list->head)
    {
        ListItem *tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    // и сам фиктивный элемент
    delete list->head;
    delete list;
}

ListItem *list_first(List *list)
{
    if (list->head->next == list->head) // список пуст
        return NULL;
    return list->head->next;
}

ListItem *list_last(List *list)
{
    if (list->last == list->head) // список пуст
        return NULL;
    return list->last;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    // если дошли до фиктивного элемента, значит список закончился
    if (item->next->dummy)
        return NULL;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    // в односвязном списке нет ссылки на предыдущий элемент
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    // вставка в начало = вставка после фиктивного элемента
    return list_insert_after(list, NULL, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    // если item == NULL, вставляем в начало (после фиктивного)
    ListItem *prev = item;
    if (prev == NULL)
        prev = list->head;

    ListItem *elem = new ListItem;
    elem->data = data;
    elem->dummy = false;
    elem->next = prev->next;
    prev->next = elem;

    // если вставили после последнего, то новый элемент стал последним
    if (prev == list->last)
        list->last = elem;

    return elem;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, NULL);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    // если item == NULL, удаляем первый элемент
    ListItem *prev = item;
    if (prev == NULL)
        prev = list->head;

    ListItem *del = prev->next;
    if (del == list->head) // после item ничего нет
        return NULL;

    prev->next = del->next;
    // если удалили последний, то последним стал prev
    if (del == list->last)
        list->last = prev;
    delete del;

    if (prev->next == list->head)
        return NULL;
    return prev->next;
}
