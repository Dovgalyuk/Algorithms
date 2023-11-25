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

    if (list->first() && list->first()->data() != 3)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    list->insert_after(list->first(), 4);

    if (list->first() && list->first()->next() && list->first()->next()->data() != 4)
    {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    // Corrected part: update the list pointer after erasing the first element
    list->erase_first();

    if (list->first() && list->first()->data() != 4)
    {
        std::cout << "list_erase error\n";
        return 1;
    }

    MyList copy(*list);

    std::cout << "List: ";
    for (auto item = copy.first(); item; item = item->next())
    {
        std::cout << item->data() << " ";
    }
    std::cout << "\n";

}
