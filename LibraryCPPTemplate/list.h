#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <utility>

using namespace std;

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return following->dummy ? nullptr : following; }
        const Item *next() const { return following->dummy ? nullptr : following; }
        Item *prev() { return previous->dummy ? nullptr : previous; }
        const Item *prev() const { return previous->dummy ? nullptr : previous; }
        Data &data() { return value; }
        const Data &data() const { return value; }

    private:
        friend class List;
        Data value;
        Item *following;
        Item *previous;
        bool dummy;

        Item(const Data &data, Item *next, Item *prev, bool is_dummy = false)
            : value(data), following(next), previous(prev), dummy(is_dummy) {}
    };

    List()
    {
        head = new Item(Data(), nullptr, nullptr, true);
        head->following = head;
        head->previous = head;
    }

    List(const List &other) : List()
    {
        for (const Item *item = other.first(); item != nullptr; item = item->next())
            insert_after(last(), item->data());
    }

    List &operator=(const List &other)
    {
        if (this != &other)
        {
            List copy(other);
            swap(head, copy.head);
        }
        return *this;
    }

    ~List()
    {
        while (first() != nullptr)
            erase_first();
        delete head;
    }

    Item *first() { return head->next(); }
    const Item *first() const { return head->next(); }
    Item *last() { return head->prev(); }
    const Item *last() const { return head->prev(); }

    Item *insert(Data data)
    {
        return insert_after(nullptr, data);
    }

    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr)
            item = head;

        Item *added = new Item(data, item->following, item);
        item->following->previous = added;
        item->following = added;
        return added;
    }

    Item *erase_first()
    {
        return erase_next(nullptr);
    }

    Item *erase_next(Item *item)
    {
        if (item == nullptr)
            item = head;

        Item *removed = item->following;
        if (removed == head)
            return nullptr;

        item->following = removed->following;
        removed->following->previous = item;
        delete removed;
        return item->next();
    }

private:
    Item *head;
};

#endif
