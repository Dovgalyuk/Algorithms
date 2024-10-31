#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data; // Данные
    ListItem* next; // Указатель на следующий элемент
};

struct List
{
    ListItem* head; // Указатель на первый элемент
};

List *list_create()
{
    return new List{nullptr}; // Инициализируем голову списка
}

void list_delete(List *list)
{
    ListItem* current = list->head;
    while (current != nullptr) {
        ListItem* next = current->next;
        delete current; // Освобождаем память
        current = next;
    }
    delete list; // Освобождаем память для списка
}

ListItem *list_first(List *list)
{
    return list->head; // Возвращаем голову списка
}

Data list_item_data(const ListItem *item)
{
    return item->data; // Возвращаем данные элемента
}

ListItem *list_item_next(ListItem *item)
{
    return item->next; // Возвращаем следующий элемент
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* newItem = new ListItem{data, list->head}; // Создаем новый элемент
    list->head = newItem; // Устанавливаем новый элемент как голову списка
    return newItem; // Возвращаем новый элемент
}

// Убедитесь, что все параметры используются или убраны
ListItem *list_insert_after(List * /*list*/, ListItem *item, Data data) {
    if (item == nullptr) return nullptr;

    ListItem* newItem = new ListItem{data, item->next};
    item->next = newItem;
    return newItem;
}


ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr) return nullptr; // Если список пуст
    ListItem* itemToRemove = list->head; // Указатель на элемент для удаления
    list->head = list->head->next; // Сдвигаем голову списка
    delete itemToRemove; // Освобождаем память
    return list->head; // Возвращаем новую голову списка
}

ListItem *list_erase_next(ListItem *item) // Изменено, чтобы использовать только item
{
    if (item == nullptr || item->next == nullptr) return nullptr; // Если нет следующего элемента
    ListItem* nextItem = item->next; // Получаем следующий элемент
    item->next = nextItem->next; // Сдвигаем указатель текущего элемента
    delete nextItem; // Удаляем следующий элемент
    return item->next; // Возвращаем новый следующий элемент
}
