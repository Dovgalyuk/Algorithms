#include <iostream>
#include "list.h"
 
int main()
{
    List *list = new List();
 
    if (!list)
        std::cout << "List creation error\n";
 
    list->push_front(1);
    list->push_front(2);
    list->push_front(3);
 
    if (list->list_first()->list_item_data() != 3)
        std::cout << "list_insert error\n";
 
    list->push_front(4);
 
    if (list->list_first()->list_item_data() != 4)
        std::cout << "list_insert_after error\n";
 
    list->list_erase_next(list->list_first());
 
    if (list->list_first()->list_item_data() != 4)
        std::cout << "list_erase error\n";
 
    std::cout << "List: ";
    for (ListItem *item = list->list_first() ; item ; item = item->list_item_next())
    {
        std::cout << item->list_item_data() << " ";
    }
    std::cout << "\n";
    
    delete list;
}