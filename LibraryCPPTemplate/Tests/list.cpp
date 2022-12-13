#include <iostream>
#include "list.h"

typedef List<int> MyList;
int main()
{
    MyList* list = new MyList;

    if (!list)
    {
        std::cout << "List creation error\n";
        return 1;
    }

    list->insert(1);
    list->insert(2);
    list->insert(3);

    if (list->list_first()->data() != 3)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    list->insert_after(list->list_first(), 4);

    if (list->list_first()->item_next()->data() != 4)
    {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    list->erase(list->list_first());

    if (list->list_first()->data() != 4)
    {
        std::cout << "list_erase error\n";
        return 1;
    }

    std::cout << "List: ";
    for (auto item = list->list_first(); item; item = item->item_next())
    {
        std::cout << item->data() << " ";
    }
    std::cout << "\n";

    delete list;
}
