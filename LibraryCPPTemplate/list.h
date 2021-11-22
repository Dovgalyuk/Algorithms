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

        Item(Data d): d(d) {}
        Item *next() { return nextItem; }
        Item *prev() { return prevItem; }
        Data data() const { return d; }
    private:
        Data d;
    };

    // Creates new list
    List(): dummyElement(new Item(0))
    {
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while (Item* item = firstItem) {
            erase(item);
            delete item;
        }
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return dummyElement->nextItem;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item* newItem = new Item(data);
        Item* firstItem = first();
        newItem->nextItem = firstItem;
        newItem->prevItem = firstItem->prevItem;
        newItem->prevItem->nextItem = newItem;
        newItem->nextItem->prevItem = newItem;
        dummyElement->nextItem = newItem;
        return newItem;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        Item* newItem = new Item(data);
        newItem->nextItem = item->nextItem;
        newItem->nextItem->prevItem = newItem;
        item->nextItem = newItem;
        newItem->prevItem = item;
        return newItem;
    }

    // Deletes the specified list item.
    // Returns pointer to the item next to the deleted one.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        Item* returned = nullptr;
        Item* firstItem = first();
        if (firstItem == item) {
            if (firstItem->nextItem == firstItem) {
                dummyElement->nextItem  = nullptr;
            } else {
                firstItem->nextItem->prevItem = firstItem->prevItem;
                firstItem->prevItem->nextItem = firstItem->nextItem;
                dummyElement->nextItem  = firstItem->nextItem;
                returned = firstItem->nextItem;
            }
        } else {
            item->nextItem->prevItem = item->prevItem;
            item->prevItem->nextItem = item->nextItem;
            returned = item->nextItem;
        }
        return returned;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return erase(item->nextItem);
    }
private:
    Item* dummyElement = nullptr;
};

#endif
