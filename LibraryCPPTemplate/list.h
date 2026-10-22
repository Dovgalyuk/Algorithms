#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() const { return next_; }
        Item *prev() const { return prev_; }

        Data &data() { return data_; }
        const Data &data() const { return data_; }

    private:
        friend class List;
        explicit Item(const Data &value)
            : data_(value), next_(nullptr), prev_(nullptr) {}

        Data data_;
        Item *next_;
        Item *prev_;
    };

    List() : head_(nullptr), tail_(nullptr) {}

    List(const List &other) : head_(nullptr), tail_(nullptr) { copy_from(other); }

    List &operator=(const List &other)
    {
        if (this != &other)
        {
            clear();
            copy_from(other);
        }
        return *this;
    }

    ~List() { clear(); }

    Item *first() const { return head_; }
    Item *last()  const { return tail_; }

    Item *insert(Data data)
    {
        Item *item = new Item(data);
        item->next_ = head_;
        if (head_) head_->prev_ = item;
        else       tail_ = item;
        head_ = item;
        return item;
    }

    Item *insert_after(Item *item, Data data)
    {
        if (!item) return insert(data);
        Item *new_item = new Item(data);
        new_item->prev_ = item;
        new_item->next_ = item->next_;
        if (item->next_) item->next_->prev_ = new_item;
        else             tail_ = new_item;
        item->next_ = new_item;
        return new_item;
    }

    Item *erase_first()
    {
        if (!head_) return nullptr;
        Item *item = head_;
        head_ = item->next_;
        if (head_) head_->prev_ = nullptr;
        else       tail_ = nullptr;
        delete item;
        return head_;
    }

    Item *erase_next(Item *item)
    {
        if (!item) return erase_first();
        Item *to_erase = item->next_;
        if (!to_erase) return nullptr;
        Item *after = to_erase->next_;
        item->next_ = after;
        if (after) after->prev_ = item;
        else       tail_ = item;
        delete to_erase;
        return after;
    }

private:
    void copy_from(const List &other)
    {
        for (Item *it = other.head_; it; it = it->next_)
        {
            Item *copy = new Item(it->data_);
            copy->prev_ = tail_;
            if (tail_) tail_->next_ = copy;
            else       head_ = copy;
            tail_ = copy;
        }
    }

    void clear()
    {
        Item *cur = head_;
        while (cur)
        {
            Item *next = cur->next_;
            delete cur;
            cur = next;
        }
        head_ = tail_ = nullptr;
    }

    Item *head_;
    Item *tail_;
};

#endif