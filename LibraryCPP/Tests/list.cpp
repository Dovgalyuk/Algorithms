#include <iostream>
#include "list.h"

int main()
{
    List* list = list_create();

    if (list == nullptr)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    if (list_first(list) != nullptr || list_last(list) != nullptr)
    {
        std::cout << "Empty list error\n";
        list_delete(list);
        return 1;
    }

    list_insert(list, 1);
    list_insert(list, 2);
    list_insert(list, 3);

    if (list_item_data(list_first(list)) != 3 ||
        list_item_data(list_last(list)) != 1)
    {
        std::cout << "Insert error\n";
        list_delete(list);
        return 1;
    }

    if (list_item_next(list_first(list)) == nullptr ||
        list_item_data(list_item_next(list_first(list))) != 2)
    {
        std::cout << "Next item error\n";
        list_delete(list);
        return 1;
    }

    if (list_item_prev(list_last(list)) == nullptr ||
        list_item_data(list_item_prev(list_last(list))) != 2)
    {
        std::cout << "Previous item error\n";
        list_delete(list);
        return 1;
    }

    list_insert_after(list, list_first(list), 4);

    if (list_item_data(list_item_next(list_first(list))) != 4)
    {
        std::cout << "Insert after error\n";
        list_delete(list);
        return 1;
    }

    list_erase_first(list);

    if (list_item_data(list_first(list)) != 4)
    {
        std::cout << "Erase first error\n";
        list_delete(list);
        return 1;
    }

    ListItem* next = list_erase_next(list, list_first(list));

    if (next == nullptr || list_item_data(next) != 1)
    {
        std::cout << "Erase next error\n";
        list_delete(list);
        return 1;
    }

    list_erase_first(list);
    list_erase_first(list);

    if (list_first(list) != nullptr || list_last(list) != nullptr)
    {
        std::cout << "Erase all error\n";
        list_delete(list);
        return 1;
    }

    list_insert_after(list, nullptr, 10);

    if (list_item_data(list_first(list)) != 10 ||
        list_item_data(list_last(list)) != 10)
    {
        std::cout << "Insert into empty list error\n";
        list_delete(list);
        return 1;
    }

    list_delete(list);

    std::cout << "List tests passed\n";
    return 0;
}