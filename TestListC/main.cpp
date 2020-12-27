#include <iostream>
#include "list.h"

int main()
{
    List *list = list_create();

    if (!list)
        std::cout << "List creation error\n";

    list_insert(list, 1);
    list_insert(list, 2);
    list_insert(list, 3);

    if (list_item_data(list_first(list)) != 3)
        std::cout << "list_insert error\n";

    list_insert_after(list, list_first(list), 4);

    if (list_item_data(list_item_next(list_first(list))) != 4)
        std::cout << "list_insert_after error\n";

    list_erase_first(list);

    if (list_item_data(list_first(list)) != 4)
        std::cout << "list_erase error\n";

    std::cout << "List: ";
    for (ListItem *item = list_first(list) ; item ; item = list_item_next(item))
    {
        std::cout << list_item_data(item) << " ";
    }
    std::cout << "\n";
    
    list_delete(list);
}
