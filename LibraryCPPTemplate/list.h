#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return nextPtr; }
        Data& data() { return value; }
        const Data& data() const { return value; }
    private:
        friend class List<Data>;

        Data value;
        Item* nextPtr;
    };

    // Creates new list
    List()
    {
        head = nullptr;
    }

    // copy constructor
    List(const List &a)
    {
        head = nullptr;

        Item* cur = a.head;
        Item* last = nullptr;

        while (cur != nullptr)
        {
            if (last == nullptr)
            {
                last = insert(cur->value);
            }
            else
            {
                last = insert_after(last, cur->value);
            }
            cur = cur->nextPtr;
        }
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this == &a)
            return *this;

        clear();

        Item* cur = a.head;
        Item* last = nullptr;

        while (cur != nullptr)
        {
            if (last == nullptr)
            {
                last = insert(cur->value);
            }
            else
            {
                last = insert_after(last, cur->value);
            }
            cur = cur->nextPtr;
        }

        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        clear();
    }

    // Retrieves the first item from the list
    Item* first() const
    {
        return head;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item* node = new Item;
        node->value = data;
        node->nextPtr = head;
        head = node;
        return node;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr)
        {
            return insert(data);
        }

        Item* node = new Item;
        node->value = data;
        node->nextPtr = item->nextPtr;
        item->nextPtr = node;

        return node;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (head == nullptr)
            return nullptr;

        Item* next = head->nextPtr;
        delete head;
        head = next;
        return head;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == nullptr)
        {
            return erase_first();
        }

        if (item->nextPtr == nullptr)
        {
            return nullptr;
        }

        Item* to_delete = item->nextPtr;
        item->nextPtr = to_delete->nextPtr;
        Item* next = item->nextPtr;

        delete to_delete;
        return next;
    }
private:
    Item* head;

    void clear()
    {
        while (head != nullptr)
        {
            erase_first();
        }
    }
};

#endif
