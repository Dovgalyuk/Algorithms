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

    if (list_first(list) || list_last(list))
    {
        std::cout << "New list is not empty\n";
        list_delete(list);
        return 1;
    }

    ListItem *one = list_insert(list, 1);
    ListItem *two = list_insert(list, 2);
    ListItem *three = list_insert(list, 3);

    if (list_first(list) != three || list_last(list) != one)
    {
        std::cout << "list_insert error\n";
        list_delete(list);
        return 1;
    }

    if (list_item_data(three) != 3 || list_item_data(two) != 2 || list_item_data(one) != 1)
    {
        std::cout << "list_item_data error\n";
        list_delete(list);
        return 1;
    }

    ListItem *four = list_insert_after(list, three, 4);

    if (list_item_next(three) != four || list_item_data(four) != 4 || list_last(list) != one)
    {
        std::cout << "list_insert_after error\n";
        list_delete(list);
        return 1;
    }

    ListItem *five = list_insert_after(list, one, 5);

    if (list_item_next(one) != five || list_last(list) != five || list_item_next(five))
    {
        std::cout << "list_insert_after at tail error\n";
        list_delete(list);
        return 1;
    }

    ListItem *six = list_insert_after(list, nullptr, 6);

    if (list_first(list) != six || list_last(list) != five)
    {
        std::cout << "list_insert_after null error\n";
        list_delete(list);
        return 1;
    }

    int expected[] = {6, 3, 4, 2, 1, 5};
    int index = 0;

    for (ListItem *item = list_first(list) ; item ; item = list_item_next(item))
    {
        if (index >= 6 || list_item_data(item) != expected[index])
        {
            std::cout << "List traversal error\n";
            list_delete(list);
            return 1;
        }

        ++index;
    }

    if (index != 6)
    {
        std::cout << "List size error\n";
        list_delete(list);
        return 1;
    }

    if (list_erase_first(list) != three || list_first(list) != three)
    {
        std::cout << "list_erase_first error\n";
        list_delete(list);
        return 1;
    }

    if (list_erase_next(list, nullptr) != four || list_first(list) != four)
    {
        std::cout << "list_erase_next null error\n";
        list_delete(list);
        return 1;
    }

    if (list_erase_next(list, four) != one || list_item_next(four) != one)
    {
        std::cout << "list_erase_next error\n";
        list_delete(list);
        return 1;
    }

    if (list_erase_next(list, one) != nullptr || list_last(list) != one || list_item_next(one))
    {
        std::cout << "list_erase_next tail error\n";
        list_delete(list);
        return 1;
    }

    if (list_erase_first(list) != one || list_first(list) != one || list_last(list) != one)
    {
        std::cout << "list_erase_first last error\n";
        list_delete(list);
        return 1;
    }

    if (list_erase_first(list) != nullptr || list_first(list) || list_last(list))
    {
        std::cout << "list_erase_first empty error\n";
        list_delete(list);
        return 1;
    }

    ListItem *seven = list_insert(list, 7);

    if (list_first(list) != seven || list_last(list) != seven || list_item_next(seven))
    {
        std::cout << "list_insert into empty error\n";
        list_delete(list);
        return 1;
    }

    if (list_item_prev(seven) != nullptr)
    {
        std::cout << "list_item_prev error\n";
        list_delete(list);
        return 1;
    }

    list_delete(list);

    std::cout << "List tests passed\n";
    return 0;
}
