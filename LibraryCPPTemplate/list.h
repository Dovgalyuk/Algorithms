#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return next_->dummy_ ? nullptr : next_; }
        Item *prev() { return prev_->dummy_ ? nullptr : prev_; }
        Data data() const { return data_; }

    private:
        friend class List;

        Item() : next_(this), prev_(this), dummy_(true) {}
        explicit Item(const Data &data) : data_(data), next_(nullptr), prev_(nullptr), dummy_(false) {}

        Item(const Item &) = delete;
        Item &operator=(const Item &) = delete;

        Data data_;
        Item *next_;
        Item *prev_;
        bool dummy_;
    };

    // Creates new list
    List()
    {
    }

    // copy constructor
    List(const List &a)
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
        return dummy_.next();
    }

    // Retrieves the last item of the list
    Item *last()
    {
        return dummy_.prev();
    }

    const Item *first() const
    {
        return dummy_.next_->dummy_ ? nullptr : dummy_.next_;
    }

    const Item *last() const
    {
        return dummy_.prev_->dummy_ ? nullptr : dummy_.prev_;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        return link_after(&dummy_, data);
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        return link_after(item ? item : &dummy_, data);
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        return erase_next(&dummy_);
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        Item *prev = item ? item : &dummy_;
        Item *victim = prev->next_;
        if (victim->dummy_)
            return nullptr;
        prev->next_ = victim->next_;
        victim->next_->prev_ = prev;
        Item *result = victim->next_->dummy_ ? nullptr : victim->next_;
        delete victim;
        return result;
    }

private:
    Item *link_after(Item *prev, const Data &data)
    {
        Item *item = new Item(data);
        item->prev_ = prev;
        item->next_ = prev->next_;
        prev->next_->prev_ = item;
        prev->next_ = item;
        return item;
    }

    void clear()
    {
        while (dummy_.next_ != &dummy_)
            erase_next(&dummy_);
    }

    void copy_from(const List &a)
    {
        try
        {
            Item *tail = &dummy_;
            for (const Item *p = a.dummy_.next_; !p->dummy_; p = p->next_)
                tail = link_after(tail, p->data_);
        }
        catch (...)
        {
            clear();
            throw;
        }
    }

    Item dummy_;
};

#endif