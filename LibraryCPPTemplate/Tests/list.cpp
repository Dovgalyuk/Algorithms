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

    *list = *list;

    {
        auto iter = list->getSimpleIterator();
        if (!iter.hasNext() || iter.peek() != 3)
        {
            std::cout << "list_insert error\n";
            delete list;
            return 1;
        }
    }

    auto first_item = list->first();
    if (!first_item)
    {
        std::cout << "list_first error\n";
        delete list;
        return 1;
    }

    list->insert_after(first_item, 4);
    MyList::Item::deleteItem(first_item);

    {
        auto iter = list->getSimpleIterator();
        iter.next();
        if (!iter.hasNext() || iter.peek() != 4)
        {
            std::cout << "list_insert_after error\n";
            delete list;
            return 1;
        }
    }

    list->erase_first();

    {
        auto iter = list->getSimpleIterator();
        if (!iter.hasNext() || iter.peek() != 4)
        {
            std::cout << "list_erase error\n";
            delete list;
            return 1;
        }
    }

    MyList copy(*list);

    std::cout << "List: ";
    list->forEach([](int value) {
        std::cout << value << " ";
        });
    std::cout << "\n";

    delete list;

    return 0;
}