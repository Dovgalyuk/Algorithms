#include <iostream>
#include "list.h"

int main()
{
    List *list = list_create();

    list_insert(list, 1);
    list_insert(list, 2);
    list_insert(list, 3);

    list_insert_after(list, list_first(list), 4);

    list_erase(list, list_first(list));

    std::cout << "List: ";
    for (ListItem *item = list_first(list) ; item ; item = list_item_next(item))
    {
        std::cout << list_item_data(item) << " ";
    }
    std::cout << "\n";
    
    list_delete(list);
}
