#ifndef LIST_H
#define LIST_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item* nextItem = nullptr;
        Item* prevItem = nullptr;
        Item(Data data): d(data) {};

        Item *next() { return nextItem; }
        Item *prev() { return prevItem; }
        Data data() const { return d; }

    protected:
        Data d;
    };

    // Creates new list
    List()
    {
    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item* item = firstItem;
        while (item) {
            Item* deleted = item;
            item = item->next();
            delete deleted;
        }
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return firstItem;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item* item = new Item(data);
        item->nextItem = firstItem;
        if (firstItem) {
            firstItem->prevItem = item;
        }
        firstItem = item;
        return item;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        Item* new_item = new Item(data);
        new_item->nextItem = item->next();
        if (new_item->next()) {
            new_item->next()->prevItem = new_item;
        }
        item->nextItem = new_item;
        new_item->prevItem = item;
        return new_item;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        if (firstItem == item) {
            firstItem = item->next();
        }
        if (item->next()) {
            item->next()->prevItem = item->prevItem;
        }
        if (item->prev()) {
            item->prev()->nextItem = item->nextItem;
        }
        auto* next = item->next();
        delete item;
        return next;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return erase(item->next());
    }

protected:
    Item* firstItem = nullptr;
};

#endif