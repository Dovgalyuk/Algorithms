#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
        friend class List;
    public:
        Item* next() { return next_; }
        Item* prev() { return nullptr; }
        Data data() const { return data_; }
    private:
        // internal data here
        Data data_;
        Item* next_;

        Item(const Data& d, Item* n) : data_(d), next_(n) {}
    };

    // Creates new list
    List() : head_(nullptr) {}

    // copy constructor
    List(const List& other) : head_(nullptr)
    {
        Item* cur = other.head_;
        Item* last = nullptr;

        while (cur) {
            Item* node = new Item(cur->data_, nullptr);
            if (!head_)
                head_ = node;
            else
                last->next_ = node;

            last = node;
            cur = cur->next_;
        }
    }

    // assignment operator
    List& operator=(const List& other)
    {
        if (this == &other) return *this;

        clear();

        Item* cur = other.head_;
        Item* last = nullptr;

        while (cur) {
            Item* node = new Item(cur->data_, nullptr);
            if (!head_)
                head_ = node;
            else
                last->next_ = node;

            last = node;
            cur = cur->next_;
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        clear();
    }

    // Retrieves the first item from the list
    Item* first()
    {
        return head_;
    }

    const Item* first() const
    {
        return head_;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data)
    {
        head_ = new Item(data, head_);
        return head_;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item* insert_after(Item* item, Data data)
    {
        if (!item)
            return insert(data);

        Item* node = new Item(data, item->next_);
        item->next_ = node;
        return node;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item* erase_first()
    {
        if (!head_) return nullptr;

        Item* next = head_->next_;
        delete head_;
        head_ = next;
        return head_;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item* erase_next(Item* item)
    {
        if (!item)
            return erase_first();

        if (!item->next_)
            return nullptr;

        Item* del = item->next_;
        item->next_ = del->next_;
        Item* res = item->next_;
        delete del;
        return res;
    }
private:
    // private data should be here
    Item* head_;

    void clear()
    {
        while (head_)
            erase_first();
    }
};

#endif
