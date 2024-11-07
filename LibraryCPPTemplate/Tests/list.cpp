#include <iostream>
#include "list.h"

typedef List<int> MyList;

int main()
{
    MyList *list = new MyList;

    if (!list)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    list->insert(1);
    list->insert(2);
    list->insert(3);

    if (list->first()->data() != 3)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    list->insert_after(list->first(), 4);

    if (list->first()->next()->data() != 4)
    {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    list->erase_first();

    if (list->first()->data() != 4)
    {
        std::cout << "list_erase error\n";
        return 1;
    }

    MyList copy(*list);

    std::cout << "List: ";
    // This loop will be executed infinitely for a ring list
    /*for (auto item = list->first() ; item ; item = item->next())
    {
        std::cout << item->data() << " ";
    }*/

    // This is a similar loop to iterate through all the values of the ring list
    List<int>::Item* item = list->first();
    if (item) {
        do {
            std::cout << item->data() << " ";
            item = item->next();
        } while (item != list->first());
    }

    delete list;
}
