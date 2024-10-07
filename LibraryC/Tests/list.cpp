#include <iostream>
#include "list.h"

void myfree(void *p)
{
    delete (int*)p;
}

int main()
{
    List *list = list_create(myfree);

    if (!list)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    list_insert(list, new int(1));
    list_insert(list, new int(2));
    list_insert(list, new int(3));

    ListItem *item = list_first(list);
    if (!item)
    {
        std::cout << "list_insert error\n";
        list_delete(list);
        return 1;
    }

    if (*(int*)list_item_data(item) != 3)
    {
        std::cout << "list_insert error\n";
        list_delete(list);
        return 1;
    }

    list_insert_after(list, list_first(list), new int(4));

    item = list_item_next(list_first(list));
    if (!item)
    {
        std::cout << "list_insert_after error\n";
        list_delete(list);
        return 1;
    }

    if (*(int*)list_item_data(item) != 4)
    {
        std::cout << "list_insert_after error\n";
        list_delete(list);
        return 1;
    }

    list_erase_first(list);

    if (*(int*)list_item_data(list_first(list)) != 4)
    {
        std::cout << "list_erase error\n";
        list_delete(list);
        return 1;
    }

    std::cout << "List: ";
    for (ListItem *it = list_first(list) ; it ; it = list_item_next(it))
    {
        std::cout << *(int*)list_item_data(it) << " ";
    }
    std::cout << "\n";

    list_delete(list);
}
