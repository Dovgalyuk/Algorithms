#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <utility>

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Item *next()
        {
            return nextItem->dummy ? nullptr : nextItem;
        }

        Item *prev()
        {
            return prevItem->dummy ? nullptr : prevItem;
        }

        Data data() const
        {
            return value;
        }

    private:
        friend class List;

        Data value;
        Item *nextItem;
        Item *prevItem;
        bool dummy;

        // Creates the dummy item
        Item()
            : value(), nextItem(this), prevItem(this), dummy(true)
        {
        }

        // Creates an item containing data
        explicit Item(const Data &data)
            : value(data), nextItem(nullptr),
              prevItem(nullptr), dummy(false)
        {
        }
    };

    // Creates an empty circular list
    List()
        : root(new Item())
    {
    }

    // Creates an independent copy
    List(const List &a)
        : root(new Item())
    {
        try
        {
            for (Item *item = a.root->nextItem;
                 item != a.root;
                 item = item->nextItem)
            {
                insert_after(last(), item->value);
            }
        }
        catch (...)
        {
            clear();
            delete root;
            throw;
        }
    }

    // Replaces the contents with a copy
    List &operator=(const List &a)
    {
        if (this != &a)
        {
            List copy(a);
            std::swap(root, copy.root);
        }

        return *this;
    }

    // Frees all items, including the dummy item
    ~List()
    {
        clear();
        delete root;
    }

    // Returns the first item
    Item *first()
    {
        return root->nextItem == root ? nullptr : root->nextItem;
    }

    // Returns the first item for a const list
    const Item *first() const
    {
        return root->nextItem == root ? nullptr : root->nextItem;
    }

    // Returns the last item
    Item *last()
    {
        return root->prevItem == root ? nullptr : root->prevItem;
    }

    // Returns the last item for a const list
    const Item *last() const
    {
        return root->prevItem == root ? nullptr : root->prevItem;
    }

    // Inserts an item at the beginning
    Item *insert(Data data)
    {
        return insert_after(nullptr, data);
    }

    // Inserts after item, or at the beginning if item is null
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr)
        {
            item = root;
        }

        Item *added = new Item(data);

        added->prevItem = item;
        added->nextItem = item->nextItem;

        item->nextItem->prevItem = added;
        item->nextItem = added;

        return added;
    }

    // Removes the first item
    Item *erase_first()
    {
        return erase_next(nullptr);
    }

    // Removes the item after item, or the first if item is null
    Item *erase_next(Item *item)
    {
        if (item == nullptr)
        {
            item = root;
        }

        Item *removed = item->nextItem;

        if (removed == root)
        {
            return nullptr;
        }

        Item *following = removed->nextItem;

        item->nextItem = following;
        following->prevItem = item;

        delete removed;

        return following == root ? nullptr : following;
    }

private:
    Item *root;

    // Removes all data items
    void clear()
    {
        while (root->nextItem != root)
        {
            erase_first();
        }
    }
};

#endif