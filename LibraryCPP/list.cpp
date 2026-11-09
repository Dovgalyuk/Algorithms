#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem(Data val, ListItem *nxt = nullptr) : data(val), next(nxt) {}
};

struct List
{
    ListItem *dummy; // Фиктивный (сторожевой) элемент
};

// Creates new list
List *list_create()
{
    List *list = new List;
    list->dummy = new ListItem((Data)0);
    list->dummy->next = list->dummy; // Замкнут сам на себя
    return list;
}

// Destroys the list and frees the memory
void list_delete(List *list)
{
    if (!list) return;
    ListItem *current = list->dummy->next;
    while (current != list->dummy)
    {
        ListItem *next_item = current->next;
        delete current;
        current = next_item;
    }
    delete list->dummy;
    delete list;
}

// Retrieves the first item from the list
ListItem *list_first(List *list)
{
    if (!list || list->dummy->next == list->dummy)
    {
        return NULL;
    }
    return list->dummy->next;
}

// Retrieves the last item of the list
ListItem *list_last(List *list)
{
    if (!list || list->dummy->next == list->dummy)
    {
        return NULL;
    }
    ListItem *current = list->dummy;
    while (current->next != list->dummy)
    {
        current = current->next;
    }
    return current;
}

// Extracts data from the list item
Data list_item_data(const ListItem *item)
{
    return item ? item->data : (Data)0;
}

// Returns list item following after the specified one
ListItem *list_item_next(ListItem *item)
{
    if (!item || item->next->next == item) // Защита от возврата фиктивного элемента при обходе
    {
        return NULL;
    }
    // Если следующий элемент — фиктивный, возвращаем NULL, чтобы избежать бесконечного цикла
    // (в зависимости от конвенций тестов, но обычно в односвязных списках конец обозначается NULL)
    return item->next;
}

// Returns previous element for the specified item.
// Not applicable for the singly linked lists.
ListItem *list_item_prev(ListItem *item)
{
    return NULL;
}

// Inserts new list item into the beginning
ListItem *list_insert(List *list, Data data)
{
    if (!list) return NULL;
    ListItem *new_item = new ListItem(data, list->dummy->next);
    list->dummy->next = new_item;
    return new_item;
}

// Inserts new list item after the specified item
// Inserts first element if item is null
ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return NULL;
    if (item == NULL)
    {
        return list_insert(list, data);
    }
    ListItem *new_item = new ListItem(data, item->next);
    item->next = new_item;
    return new_item;
}

// Deletes the first list item.
// Returns pointer to the item next to the deleted one.
ListItem *list_erase_first(List *list)
{
    if (!list || list->dummy->next == list->dummy)
    {
        return NULL;
    }
    ListItem *target = list->dummy->next;
    list->dummy->next = target->next;
    ListItem *next_item = target->next;
    delete target;

    if (next_item == list->dummy)
    {
        return NULL;
    }
    return next_item;
}

// Deletes the list item following the specified one.
// Deletes the first element when item is null.
// Returns pointer to the item next to the deleted one.
// Should be O(1)
ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list) return NULL;
    if (item == NULL)
    {
        return list_erase_first(list);
    }

    ListItem *target = item->next;
    if (target == list->dummy)
    {
        return NULL; // Нельзя удалять фиктивный элемент
    }

    item->next = target->next;
    ListItem *next_item = target->next;
    delete target;

    if (next_item == list->dummy)
    {
        return NULL;
    }
    return next_item;
}
