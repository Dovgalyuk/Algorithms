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

    MyList orderedList;
    auto* first = orderedList.insert(1);
    auto* second = orderedList.insert_after(first, 2);
    auto* third = orderedList.insert_after(second, 3);

    auto* returned = orderedList.erase_next(first);
    if (returned != third || returned->data() != 3)
    {
        std::cout << "value error";
        return 1;
    }

    if (first->next() != third || third->prev() != first)
    {
        std::cout << "fail after erase_next";
        return 1;
    }

    MyList copiedList(orderedList);
    if (!copiedList.first() || copiedList.first()->data() != 1)
    {
        std::cout << "miss head";
        return 1;
    }
    if (!copiedList.first()->next() || copiedList.first()->next()->data() != 3)
    {
        std::cout << "miss tail";
        return 1;
    }

    MyList copy(*list);

    std::cout << "List: ";
    for (auto item = list->first() ; item ; item = item->next())
    {
        std::cout << item->data() << " ";
    }
    std::cout << "\n";

    delete list;
}
