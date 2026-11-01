#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return (next_ == fict_) ? nullptr : next_; }
        Item *prev() { return (prev_ == fict_) ? nullptr : prev_; }
        Data data() const { return data_; }
    private:
        friend class List<Data>;
        Item *next_;
        Item *prev_;
        Item *fict_;
        Data data_;
    };

    // Creates new list
    List()
    {
        fict=new Item();
        fict->next_ =fict;
        fict->prev_ =fict;
        fict->fict_ =fict;
    }

    // copy constructor
    List(const List &a)
    {
        fict = new Item();
        fict->next_=fict;
        fict->prev_ =fict;
        fict->fict_ =fict;
        copy_from(a);
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this!= &a ) {
            clear();
            copy_from(a);
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        clear();
        delete fict;
    }

    // Retrieves the first item from the list
    Item *first() const
    {
        return to_external(fict->next_);
    }

    // Retrieves the last item of the list
    Item *last() const
    {
        return to_external(fict->prev_);
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        return insert_after(nullptr,data);
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        Item *prevNode =to_internal(item);
        Item *newItem =new Item();
        newItem->data_ =data;
        newItem->fict_ =fict;
        newItem->prev_ = prevNode;
        newItem->next_ = prevNode->next_;
        prevNode->next_->prev_ =newItem;
        prevNode->next_ = newItem;
        return newItem;
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
        Item *prevNode =to_internal(item);
        Item *target= prevNode->next_;
        if (target == fict) return nullptr;

        prevNode->next_ = target->next_;
        target->next_->prev_ = prevNode;
        Item *nextItem = target->next_;
        delete target;
        return to_external(nextItem);
    }
private:
    Item *fict;
    void clear() {
        while(fict->next_ != fict) erase_first();
    }
    void copy_from(const List &a) {
        Item *last= nullptr;
        for (Item *curr = a.fict->next_;curr != a.fict; curr = curr->next_) {
            last = insert_after(last, curr->data_);
        }
    }
    Item *to_internal(Item *external) const {
        return external ? external : fict;
    }
    Item *to_external(Item *internal) const {
        return (internal==fict) ? nullptr : internal;
    }
};

#endif
