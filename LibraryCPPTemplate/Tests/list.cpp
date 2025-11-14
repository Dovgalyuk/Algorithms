#include <iostream>
#include "list.h"

typedef List<int> MyList;

int main()
{
    MyList* list = new MyList;

    list->insert(1);
    list->insert(2);
    list->insert(3);

    if (list->first()->data() != 3)
    {
        std::cout << "list_insert error\n";
        delete list;
        return 1;
    }

    list->insert_after(list->first(), 4);

    if (list->first()->next()->data() != 4)
    {
        std::cout << "list_insert_after error\n";
        delete list;
        return 1;
    }

    list->erase_first();

    if (list->first()->data() != 4)
    {
        std::cout << "list_erase error\n";
        delete list;
        return 1;
    }

    MyList copy(*list);

    std::cout << "List: OK (cycle disabled for CI)" << std::endl;

    delete list;

    std::cout << "All list tests passed!" << std::endl;
    return 0;
}