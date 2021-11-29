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
    List() {
        dummyElement = new Item(0);
        dummyElement->nextItem = dummyElement;
        dummyElement->prevItem = dummyElement;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while (Item* item = first()) {
            erase(item);
            delete item;
        }
        delete dummyElement;
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return empty() ? nullptr : dummyElement->nextItem;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        return insert_after(dummyElement, data);
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

    bool empty() {
        return dummyElement->nextItem == dummyElement;
    }

    // Deletes the specified list item.
    // Returns pointer to the item next to the deleted one.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        item->nextItem->prevItem = item->prevItem;
        item->prevItem->nextItem = item->nextItem;
        Item* returned = item->nextItem;
        delete item;
        return empty() ? nullptr : returned;
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
