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
        void setData(Data data) {
            data_ = data;
        }
        void setNext(Item* next) {
            next_ = next;
        }
        void setPrev(Item* prev) {
            prev_ = prev;
        }
    protected:
        // internal data here
        Item *next_;
        Item *prev_;
        Data data_;
    };

    // Creates new list
        List()
    {
        head_ = nullptr;
        tail_ = nullptr;
    }

    // copy constructor
    template <typename T>
    List(const List<T> &a)
    {
        head_ = nullptr;
        tail_ = nullptr;
        
        for (Item* item = a.first(); item != nullptr; item = item->next())
        {
            insert(item->data());
        }
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return head_;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item *new_item = new Item();
        new_item->setData(data);

        if (head_ == nullptr)
        {
            head_ = new_item;
            tail_ = new_item;
        }
        else
        {
            new_item->setNext(head_);
            head_->setPrev(new_item);
            head_ = new_item;
        }

        return new_item;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr)
        {
        }

        Item *new_item = new Item();
        new_item->setData(data);

        new_item->setNext(item->next());
        if (item->next() != nullptr)
        {
            item->next()->setPrev(new_item);
        }
        else
        {
            tail_ = new_item;
        }
        new_item->setPrev(item);
        item->setNext(new_item);

        return new_item;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (head_ == nullptr)
        {
        }

        Item *item = head_;
        Item *next_item = item->next();

        if (next_item != nullptr)
        {
            next_item->setPrev(nullptr);
        }
        else
        {
            tail_ = nullptr;
        }
        head_ = next_item;

        delete item;
        return next_item;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == nullptr)
        {
        }

        Item *erased_item = item->next();
        if (erased_item == nullptr)
        {
        }

        Item *next_item = erased_item->next();

        item->setNext(next_item);
        if (next_item != nullptr)
        {
            next_item->setPrev(item);
        }
        else
        {
            tail_ = item;
        }

        delete erased_item;
        return next_item;
    }

protected:
    // private data should be here
    Item *head_;
    Item *tail_;
};

#endif
