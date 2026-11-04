#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

using namespace std;

template <typename Data> class List
{
public:
    class Item
    {
        friend class List;

    public:
        Item *next()
        {
            return next_item->is_dummy ? nullptr : next_item;
        }

        Item *prev()
        {
            return prev_item->is_dummy ? nullptr : prev_item;
        }

        Data data() const { return value; }

    private:
        // internal data here
        Data value;
        Item *next_item;
        Item *prev_item;
        bool is_dummy;

        Item() : value(), next_item(this), prev_item(this), is_dummy(true) {}

        explicit Item(const Data &data)
            : value(data), next_item(this), prev_item(this), is_dummy(false) {}
    };

    // Creates new list
    List()
    {
    }

    // copy constructor
    List(const List &a) : List()
    {
        for (Item *item = a.head.next_item; item != &a.head; item = item->next_item)
            insert_after_node(head.prev_item, item->value);
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this != &a)
        {
            while (first())
                erase_first();

            for (Item *item = a.head.next_item; item != &a.head; item = item->next_item)
                insert_after_node(head.prev_item, item->value);
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while (first())
            erase_first();
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return head.next_item == &head ? nullptr : head.next_item;
    }

    // Retrieves the last item of the list
    Item *last()
    {
        return head.prev_item == &head ? nullptr : head.prev_item;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        return insert_after_node(&head, data);
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        return insert_after_node(item ? item : &head, data);
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        return erase_after_node(&head);
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return erase_after_node(item ? item : &head);
    }

private:
    // private data should be here
    Item head;

    Item *insert_after_node(Item *node, const Data &data)
    {
        Item *item = new Item(data);
        item->next_item = node->next_item;
        item->prev_item = node;
        node->next_item->prev_item = item;
        node->next_item = item;
        return item;
    }

    Item *erase_after_node(Item *node)
    {
        Item *removed = node->next_item;
        if (removed == &head)
            return nullptr;

        Item *next = removed->next_item;
        node->next_item = next;
        next->prev_item = node;
        delete removed;
        return next == &head ? nullptr : next;
    }
};

#endif
