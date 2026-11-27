#include <iostream>
#include "list.h"

int main()
{
    List *list = list_create();

    if (!list)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    if (list_first(list) != nullptr || list_last(list) != nullptr)
    {
        std::cout << "New list is not empty\n";
        list_delete(list);
        return 1;
    }

    if (list_erase_first(list) != nullptr || list_erase_next(list, nullptr) != nullptr)
    {
        std::cout << "Empty list erase error\n";
        list_delete(list);
        return 1;
    }

    list_insert(list, 1);
    list_insert(list, 2);
    list_insert(list, 3);

    if (list_item_data(list_first(list)) != 3)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    if (list_item_data(list_last(list)) != 1)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    if (list_item_prev(list_first(list)) != nullptr ||
        list_item_prev(list_item_next(list_first(list))) != list_first(list) ||
        list_item_next(list_last(list)) != nullptr)
    {
        std::cout << "Invalid list links after insert\n";
        list_delete(list);
        return 1;
    }

    list_insert_after(list, list_first(list), 4);

    if (list_item_data(list_item_next(list_first(list))) != 4)
    {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    if (list_item_prev(list_item_next(list_first(list))) != list_first(list))
    {
        std::cout << "Invalid previous link after insert_after\n";
        list_delete(list);
        return 1;
    }

    list_erase_first(list);

    if (list_item_data(list_first(list)) != 4)
    {
        std::cout << "list_erase error\n";
        return 1;
    }

    if (list_item_prev(list_first(list)) != nullptr)
    {
        std::cout << "Invalid first previous link after erase\n";
        list_delete(list);
        return 1;
    }

    ListItem *first = list_first(list);
    ListItem *after_erased = list_erase_next(list, first);
    if (after_erased != list_last(list) || list_item_data(after_erased) != 1 ||
        list_item_prev(after_erased) != first)
    {
        std::cout << "list_erase_next error\n";
        list_delete(list);
        return 1;
    }

    if (list_erase_next(list, first) != nullptr || list_last(list) != first ||
        list_item_next(first) != nullptr)
    {
        std::cout << "Last item erase error\n";
        list_delete(list);
        return 1;
    }

    std::cout << "List: ";
    for (ListItem *item = list_first(list) ; item ; item = list_item_next(item))
    {
        std::cout << list_item_data(item) << " ";
    }
    std::cout << "\n";

    list_erase_first(list);
    if (list_first(list) != nullptr || list_last(list) != nullptr)
    {
        std::cout << "List is not empty after final erase\n";
        list_delete(list);
        return 1;
    }

    list_delete(list);
}
