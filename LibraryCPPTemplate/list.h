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
        Data data() const { return data_; }
    private:
        friend class List;
        explicit Item(const Data &d) : next_(nullptr), prev_(nullptr), data_(d) {}
        Item *next_;
        Item *prev_;
        Data data_;
    };

    // Creates new list
    List() : head_(nullptr), tail_(nullptr)
    {
    }

    // copy constructor
    List(const List &a) : head_(nullptr), tail_(nullptr)
    {
        copyFrom(a);
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this != &a)
        {
            clear();
            copyFrom(a);
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

    // Retrieves the last item of the list
    Item *last()
    {
        return tail_;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        return insert_after(nullptr, data);
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        Item *n = new Item(data);
        if (item == nullptr)
        {
            n->next_ = head_;
            if (head_) head_->prev_ = n;
            else tail_ = n;
            head_ = n;
        }
        else
        {
            n->prev_ = item;
            n->next_ = item->next_;
            if (item->next_) item->next_->prev_ = n;
            else tail_ = n;
            item->next_ = n;
        }
        return n;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        return erase_next(nullptr);
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        Item *target = item ? item->next_ : head_;
        if (target == nullptr) return nullptr;
        Item *after = target->next_;

        if (target->prev_) target->prev_->next_ = target->next_;
        else head_ = target->next_;
        if (target->next_) target->next_->prev_ = target->prev_;
        else tail_ = target->prev_;

        delete target;
        return after;
    }

private:
    Item *head_;
    Item *tail_;

    void clear()
    {
        while (head_) erase_first();
    }
    void copyFrom(const List &a)
    {
        Item *last = nullptr;
        for (Item *p = a.head_; p; p = p->next_)
            last = insert_after(last, p->data_);
    }
};

#endif