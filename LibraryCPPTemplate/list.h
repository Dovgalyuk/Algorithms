#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return nextItem; }
        const Item *next() const { return nextItem; }
        Item *prev() { return prevItem; }
        const Item *prev() const { return prevItem; }
        Data& data() { return value; }
        const Data& data() const { return value; }

    private:
        // internal data here
        friend class List<Data>;

        Item(const Data& data) : nextItem(nullptr), prevItem(nullptr), value(data)
        {
        }

        Item *nextItem;
        Item *prevItem;
        Data value;
    };

    // Creates new list
    List() : firstItem(nullptr), lastItem(nullptr)
    {
    }

    // copy constructor
    List(const List &a) : firstItem(nullptr), lastItem(nullptr)
    {
        for (const Item *current = a.first(); current != nullptr; current = current->next())
        {
            insert_after(lastItem, current->data());
        }
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this == &a) return *this;

        List copy(a);
        Item *oldFirst = firstItem;
        Item *oldLast = lastItem;

        firstItem = copy.firstItem;
        lastItem = copy.lastItem;
        copy.firstItem = oldFirst;
        copy.lastItem = oldLast;

        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while (firstItem != nullptr)
        {
            erase_first();
        }
    }

    // Retrieves the first item from the list
    Item *first() { return firstItem; }
    const Item *first() const { return firstItem; }

    // Retrieves the last item from the list
    Item *last() { return lastItem; }
    const Item *last() const { return lastItem; }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item *newItem = new Item(data);
        newItem->nextItem = firstItem;

        if (firstItem != nullptr) firstItem->prevItem = newItem;
        else lastItem = newItem;

        firstItem = newItem;
        return newItem;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr) return insert(data);

        Item *newItem = new Item(data);
        newItem->prevItem = item;
        newItem->nextItem = item->nextItem;

        if (item->nextItem != nullptr) item->nextItem->prevItem = newItem;
        else lastItem = newItem;

        item->nextItem = newItem;
        return newItem;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (firstItem == nullptr) return nullptr;

        Item *nextItem = firstItem->nextItem;
        delete firstItem;
        firstItem = nextItem;

        if (firstItem != nullptr) firstItem->prevItem = nullptr;
        else lastItem = nullptr;

        return firstItem;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == nullptr) return erase_first();
        if (item->nextItem == nullptr) return nullptr;

        Item *removed = item->nextItem;
        Item *nextItem = removed->nextItem;
        item->nextItem = nextItem;

        if (nextItem != nullptr) nextItem->prevItem = item;
        else lastItem = item;

        delete removed;
        return nextItem;
    }

private:
    // private data should be here
    Item *firstItem;
    Item *lastItem;
};

#endif
