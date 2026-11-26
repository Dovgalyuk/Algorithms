#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return next_; }
        Item *prev() { return prev_; }
        const Item *next() const { return next_; }
        const Item *prev() const { return prev_; }
        Data &data() { return data_; }
        const Data &data() const { return data_; }
    private:
        friend class List<Data>;
        Data data_;
        Item *next_ = nullptr;
        Item *prev_ = nullptr;

        Item(const Data &data, Item *prev = nullptr, Item *next = nullptr)
            : data_(data), next_(next), prev_(prev)
        {
        }
    };

    // Creates new list
    List() : head_(nullptr), tail_(nullptr)
    {
    }

    // copy constructor
    List(const List &a) : head_(nullptr), tail_(nullptr)
    {
        copy_from(a);
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this != &a)
        {
            clear();
            copy_from(a);
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        clear();
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return head_;
    }

    const Item *first() const
    {
        return head_;
    }

    // Retrieves the last item of the list
    Item *last()
    {
        return tail_;
    }

    const Item *last() const
    {
        return tail_;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item *item = new Item(data, nullptr, head_);
        if (head_)
        {
            head_->prev_ = item;
        }
        else
        {
            tail_ = item;
        }
        head_ = item;
        return item;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        if (!item)
        {
            return insert(data);
        }
        Item *new_item = new Item(data, item, item->next_);
        if (item->next_)
        {
            item->next_->prev_ = new_item;
        }
        else
        {
            tail_ = new_item;
        }
        item->next_ = new_item;
        return new_item;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (!head_)
        {
            return nullptr;
        }
        Item *next = head_->next_;
        delete head_;
        head_ = next;
        if (head_)
        {
            head_->prev_ = nullptr;
        }
        else
        {
            tail_ = nullptr;
        }
        return head_;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (!item)
        {
            return erase_first();
        }
        Item *to_delete = item->next_;
        if (!to_delete)
        {
            return nullptr;
        }
        Item *next = to_delete->next_;
        item->next_ = next;
        if (next)
        {
            next->prev_ = item;
        }
        else
        {
            tail_ = item;
        }
        delete to_delete;
        return next;
    }

    // Deletes the specified item directly
    Item *erase(Item *item)
    {
        if (!item)
        {
            return nullptr;
        }
        if (item == head_)
        {
            return erase_first();
        }
        return erase_next(item->prev_);
    }

private:
    Item *head_ = nullptr;
    Item *tail_ = nullptr;

    void clear()
    {
        while (head_)
        {
            erase_first();
        }
    }

    void copy_from(const List &a)
    {
        for (const Item *cur = a.first(); cur != nullptr; cur = cur->next())
        {
            insert_after(tail_, cur->data());
        }
    }
};

#endif
