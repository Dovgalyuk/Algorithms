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
        Item(const Data &data) : data_(data) , next_(nullptr), prev_(nullptr) {}
        Data data_;
        Item *next_;
        Item *prev_;
    };

    // Creates new list
    List(): head_(nullptr), tail_(nullptr)
    {
    }

    // copy constructor
    List(const List &a): head_(nullptr), tail_(nullptr)
    {
        copyFrom(a);
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this != &a) {
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
        Item *node = new Item(data);
        node->next_ = head_;
        if (head_ != nullptr) {
            head_->prev_ = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        return node;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {

        if (item == nullptr) {
            return insert(data);
        }
        Item *node = new Item(data);
        node->prev_ = item;
        node->next_ = item->next_;
        if (item->next_ != nullptr) {
            item->next_->prev_ = node;
        } else {
            tail_ = node;
        }
        item->next_ = node;
        return node;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (head_ == nullptr) {
            return nullptr;
        }
        Item *removed = head_;
        Item *next_item = removed->next_;
        head_ = next_item;
        if (next_item != nullptr) {
            next_item->prev_ = nullptr;
        }else {
            tail_ = nullptr;
        }
        delete removed;
        return next_item;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == nullptr) {
            return erase_first();
        }
        if (item->next_ == nullptr) {
            return nullptr;
        }
        Item *removed = item->next_;
        Item *next_item = removed->next_;
        item->next_ = next_item;
        if (next_item != nullptr) {
            next_item->prev_ = item;
        }else {
            tail_ = item;
        }
        delete removed;
        return next_item;
    }
private:
    // private data should be here
    void clear(){
        while (head_ != nullptr) {
            erase_first();
        }
    }

    void copyFrom(const List &a)
    {
        Item *lastCopied = nullptr;
        for (Item *p = a.head_; p != nullptr; p = p->next_) {
            lastCopied = insert_after(lastCopied, p->data_);
        }
    }

    Item *head_;
    Item *tail_;
};

#endif
