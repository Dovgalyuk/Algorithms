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

    list_insert(list, 1);
    list_insert(list, 2);
    list_insert(list, 3);

    if (list_item_data(list_first(list)) != 3)
    {
        std::cout << "list_insert error\n";
        list_delete(list);
        return 1;
    }

    if (list_item_data(list_last(list)) != 1)
    {
        std::cout << "list_insert error\n";
        list_delete(list);
        return 1;
    }

    // Проверка list_item_prev при обходе назад
    if (list_item_prev(list_first(list)) != nullptr)
    {
        std::cout << "list_item_prev head error\n";
        list_delete(list);
        return 1;
    }

    ListItem *last = list_last(list);
    if (!last || list_item_data(list_item_prev(last)) != 2)
    {
        std::cout << "list_item_prev error\n";
        list_delete(list);
        return 1;
    }

    list_insert_after(list, list_first(list), 4);

    if (list_item_data(list_item_next(list_first(list))) != 4)
    {
        std::cout << "list_insert_after error\n";
        list_delete(list);
        return 1;
    }

    // Проверка связей prev после insert_after
    ListItem *fourth = list_item_next(list_first(list));
    if (list_item_prev(fourth) != list_first(list))
    {
        std::cout << "list_insert_after prev pointer error\n";
        list_delete(list);
        return 1;
    }

    list_erase_first(list);

    if (list_item_data(list_first(list)) != 4)
    {
        std::cout << "list_erase error\n";
        list_delete(list);
        return 1;
    }

    if (list_item_prev(list_first(list)) != nullptr)
    {
        std::cout << "list_erase_first prev pointer error\n";
        list_delete(list);
        return 1;
    }

    // Проверка list_erase_next
    // Текущий список: 4, 2, 1
    list_erase_next(list, list_first(list));
    // После удаления элемента после 4: список 4, 1
    if (list_item_data(list_item_next(list_first(list))) != 1)
    {
        std::cout << "list_erase_next error\n";
        list_delete(list);
        return 1;
    }
    if (list_item_prev(list_last(list)) != list_first(list))
    {
        std::cout << "list_erase_next prev pointer error\n";
        list_delete(list);
        return 1;
    }

    std::cout << "List: ";
    for (ListItem *item = list_first(list); item; item = list_item_next(item))
    {
        std::cout << list_item_data(item) << " ";
    }
    std::cout << "\n";

    list_delete(list);
    return 0;
}
