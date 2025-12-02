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

    *list = *list;
    
    if (list->first()->f_data() != 3)
    {
        std::cout << "list_insert error\n";
        return 1;
    }

    list->insert_after(list->first(), 4);

    if (list->first()->f_next()->f_data() != 4)
    {
        std::cout << "list_insert_after error\n";
        return 1;
    }

    list->erase_first();

    if (list->first()->f_data() != 4)
    {
        std::cout << "list_erase error\n";
        return 1;
    }

    MyList copy(*list);

    std::cout << "List: ";
    for (auto item = list->first(), last=list->first()->f_prev() ; item ; item = item->f_next())
    {
        std::cout << item->f_data() << " ";
        if (item == last)
        {
            break;
        }
    }
    std::cout << "\n";

    delete list;
}
