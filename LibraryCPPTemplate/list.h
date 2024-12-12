#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Item(Data data) : dataa(data), nextt(nullptr), prevv(nullptr) {}

        Item *next() { return nextt; }
        Item *prev() { return prevv; }
        Data data()  { return dataa; }

    private:
        Data dataa;
        Item *nextt;
        Item *prevv;

        friend class List<Data>;
    };

    // Creates new list
    List() : head(nullptr), tail(nullptr), size(0) {}

    // Copy constructor
    List(const List &a)
    {
        head = tail = nullptr;
        size = 0;
        for (Item *current = a.head; current != nullptr; current = current->nextt)
        {
            insert(current->dataa);
        }
    }

    // Assignment operator
    List &operator=(const List &a)
    {
        if (this != &a)
        {
            while (head)
            {
                erase_first();
            }

            for (Item *current = a.head; current != nullptr; current = current->nextt)
            {
                insert(current->dataa);
            }
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while (head)
        {
            erase_first();
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
        Item *new_item = new Item(data);
        if (head == nullptr)
        {
            head = tail = new_item;
        }
        else
        {
            new_item->nextt = head;
            head->prevv = new_item;
            head = new_item;
        }
        size++;
        return new_item;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr)
            return nullptr;

        Item *new_item = new Item(data);
        new_item->nextt = item->nextt;
        new_item->prevv = item;

        if (item->nextt)
        {
            item->nextt->prevv = new_item;
        }
        item->nextt = new_item;

        if (item == tail)
        {
            tail = new_item;
        }

        size++;
        return new_item;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (head == nullptr)
            return nullptr;

        Item *temp = head;
        head = head->nextt;

        if (head)
        {
            head->prevv = nullptr;
        }
        else
        {
            tail = nullptr;
        }

        size--;
        delete temp;
        return head;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == nullptr || item->nextt == nullptr)
            return nullptr;

        Item *to_delete = item->nextt;
        item->nextt = to_delete->nextt;

        if (to_delete->nextt)
        {
            to_delete->nextt->prevv = item;
        }
        else
        {
            tail = item;
        }

        size--;
        delete to_delete;
        return item->nextt;
    }

private:
    Item *head;
    Item *tail;
    size_t size;
};

#endif
