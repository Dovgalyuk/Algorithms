#ifndef LIST_H
#define LIST_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return nullptr; }
        Item *prev() { return nullptr; }
        Data data() const { return Data(); }
    private:
        // internal data here
    };

    // Creates new list
    List()
    {
    }

    // Destroys the list and frees the memory
    ~List()
    {
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return nullptr;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        return nullptr;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        return nullptr;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        return nullptr;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return nullptr;
    }
private:
    // private data should be here
};

#endif
