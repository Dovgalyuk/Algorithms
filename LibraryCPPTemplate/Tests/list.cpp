#include <iostream>
#include <stdexcept>
#include <string>
#include "list.h"

using namespace std;

typedef List<int> MyList;


typedef List<string> StringList;

void check(bool condition, const char *message)
{
    if (!condition)
        throw runtime_error(message);
}

void test_list()
{
    StringList list;
    check(list.first() == nullptr && list.last() == nullptr, "Empty list");
    check(list.erase_first() == nullptr, "Erase empty list");
    auto first = list.insert("one");
    auto last = list.insert_after(first, "three");
    auto middle = list.insert_after(first, "two");
    check(first->next() == middle && middle->next() == last, "List next");
    check(last->prev() == middle && middle->prev() == first, "List prev");
    check(first->prev() == nullptr && last->next() == nullptr, "List boundaries");
    check(list.erase_next(first) == last && last->prev() == first, "Erase middle");
    check(list.erase_next(last) == nullptr && list.last() == last, "Erase after last");

    StringList copy(list);
    copy.first()->data() = "changed";
    check(list.first()->data() == "one", "List independent copy");
    copy.erase_first();
    check(copy.first()->data() == "three", "List copy order");
    copy = list;
    copy = copy;
    check(copy.first()->data() == "one", "List assignment");

    check(list.erase_next(first) == nullptr && list.last() == first, "Erase last");
    check(list.erase_first() == nullptr && list.first() == nullptr, "Erase only");
    check(list.last() == nullptr, "List empty tail");
    list.insert("again");
    check(list.first()->data() == "again", "List reuse");
    copy = StringList();
    check(copy.first() == nullptr, "Assign empty list");
}

int main()
{
    try
    {
        test_list();
    }
    catch (const exception &error)
    {
        cerr << error.what() << '\n';
        return 1;
    }

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

    if (list->last()->data() != 1)
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
    for (auto item = list->first() ; item ; item = item->next())
    {
        std::cout << item->data() << " ";
    }
    std::cout << "\n";

    delete list;
}
