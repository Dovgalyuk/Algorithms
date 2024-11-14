    #include <iostream>
    #include "list.h"

    int main()
    {
        List *list = new List;

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

        List copy(*list);

        std::cout << "List: ";

        for (auto item = list->first() ; item ; item = item->next())
        {
            {   
                std::cout << item->data() << " ";
            }
            std::cout << "\n";
        }

        list->insert(5);
        list->insert_after(list->first()->next(), 8);

        if (list->first()->next()->next()->data() != 8)
        {
            std::cout << "list_insert_after multiple error\n";
            return 1;
        }

        auto item_erase = list->first()->next();
        auto erased_item = list->erase_next(item_erase);

        if (erased_item->data() != 2)
        {
            std::cout << "list_erase_next error\n";
            return 1;
        }

        list->~List();

        if (list->first() != nullptr)
        {
            std::cout << "list_clear error\n";
            return 1;
        }

        list->insert(7);
        if (list->first()->data() != 7)
        {
            std::cout << "push after empty list error\n";
            return 1;
        }

        delete list;

        return 0;
    }
