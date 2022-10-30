#ifndef LIST_H
#define LIST_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *nextItem = nullptr;
        Item *prevItem = nullptr;
        Item *next() { return nextItem; }
        Item *prev() { return prevItem; }
        Data data() const { return Data(); }

        Item(Data newData) 
        {
            dataItem = newData;
        }
    private:
        // internal data here
        Data dataItem;
    };

    // Creates new list
    List()
    {
        head = nullptr;
    }

    // Destroys the list and frees the memory
    ~List()
    {     while (head)
          {
            Item *temp = head;
            head = head->next();
            delete temp;
          }
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return head;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item *item = new Item(data);
        item->nextItem = head;

        if (head) 
        {
            head->prevItem = item;
        }

        head = item;
        return item;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        Item *NewItem = new Item(data);
        NewItem->nextItem = item->next();

        if (NewItem->next()) 
        {
            NewItem->next()->prevItem = NewItem;
        } 

        item->nextItem = NewItem;
        NewItem->prevItem = item;
        return NewItem;
    }

    // Deletes the specified list item.
    // Returns pointer to the item next to the deleted one.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        if (head == item) 
        {
            head = item->next();
        }

        if (item->next()) 
        {
            item->next()->prevItem = item->prevItem;
        }

        if (item->prev()) 
        {
            item->prev()->nextItem = item->nextItem;
        }

        auto *next = item->next();
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
private:
    // private data should be here
    Item *head;
};
#endif
