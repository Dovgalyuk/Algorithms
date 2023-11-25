#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Item *next() { return next_; }
        Item *prev() { return prev_; }
        Data data() const { return data_; }
        Item(){
            setNext(nullptr);
            setPrev(nullptr);
        }
        void setData(Data data)
        {
            data_ = data;
        }
        void setNext(Item *next)
        {
            next_ = next;
        }
        void setPrev(Item *prev)
        {
            prev_ = prev;
        }

    private:
        Item *next_;
        Item *prev_;
        Data data_;
    };

    List()
    {
        first_ = nullptr;
    }

    ~List()
    {
        while (first_ != nullptr)
        {
            Item *tmp = first_->next();
            first_->setNext(nullptr);
            first_->setPrev(nullptr);
            delete first_;
            first_ = tmp;
        }
    }

    Item *first()
    {
        return first_;
    }

    Item *insert(Data data)
    {
        Item *newItem = new Item;
        newItem->setData(data);
        newItem->setPrev(NULL);
        newItem->setNext(first_);

        if (first_ != NULL)
        {
            first_->setPrev(newItem);
        }

        first_ = newItem;

        return newItem;
    }

    Item *insert_after(Item *prev_item, Data data)
    {
        if (prev_item == NULL)
        {
            return NULL;
        }

        Item *newItem = new Item;
        newItem->setData(data);
        newItem->setNext(prev_item->next());
        newItem->setPrev(prev_item);

        if (prev_item->next() != NULL)
        {
            prev_item->next()->setPrev(newItem);
        }

        prev_item->setNext(newItem);

        return newItem;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item* erase_first()
{
    Item *firstItem = first_;

    if (firstItem != NULL)
    {
        first_ = firstItem->next();

        if (first_ != NULL)
        {
            first_->setPrev(NULL);
        }

        delete firstItem;
    }

    return first_;
}

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == NULL || item->next() == NULL)
        {
            return NULL; 
        }

        Item *nextItem = item->next();
        item->setNext(nextItem->next());

        if (nextItem->next() != NULL)
        {
            nextItem->next()->setPrev(item);
        }

        delete nextItem;

        return item->next();
    }

private:
    // private data should be here
    Item *first_;
};

#endif