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

    if (*(int*)list_item_data(list_first(list)) != 3)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    list_insert_after(list, list_first(list), new int(4));

    if (*(int*)list_item_data(list_item_next(list_first(list))) != 4)
    {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    list_erase(list, list_first(list));

    if (*(int*)list_item_data(list_first(list)) != 4)
    {
        std::cout << "list_erase error\n";
        return 1;
    }

    std::cout << "List: ";
    for (ListItem *item = list_first(list) ; item ; item = list_item_next(item))
    {
        std::cout << *(int*)list_item_data(item) << " ";
    }
    std::cout << "\n";

    list_delete(list);
}
