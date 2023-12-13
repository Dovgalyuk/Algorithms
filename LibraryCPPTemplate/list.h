#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item(Data data, Item* prev = nullptr, Item* next = nullptr) : data_(data), prev_(prev), next_(next) {}
        
        Item* next() { return next_; }
        Item* prev() { return prev_; }
        Data data() const { return data_; }

        void setPrev(Item* prev) { prev_ = prev; }
        void setNext(Item* next) { next_ = next; }

    private:
        Data data_;
        Item* prev_;
        Item* next_;
    };

    List()
    {
        head_ = nullptr;
        tail_ = nullptr;
    }

    // copy constructor
    List(const List &a)
    {
        head_ = nullptr;
        tail_ = nullptr;
        Item* current = a.head_;
        while (current)
        {
            insert(current->data());
            current = current->next();
        }
    }

    List &operator=(const List &a)
    {
        if (this != &a)
        {
            while (head_)
            {
                Item* temp = head_;
                head_ = head_->next();
                delete temp;
            }

            Item* lastInserted = nullptr;
            Item* current = a.head_;
            while (current)
            {
                if (lastInserted == nullptr)
                {
                    lastInserted = insert(current->data());
                }
                else
                {
                    lastInserted = insert_after(lastInserted, current->data());
                }
                current = current->next();
            }
        }
        return *this;
    }

    ~List()
    {
        while (head_)
        {
            Item* temp = head_;
            head_ = head_->next();
            delete temp;
        }
    }

    Item *first()
    {
        return head_;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item* newItem = new Item(data, nullptr, head_);
        if (head_)
        {
            head_->setPrev(newItem);
        }
        else
        {
            tail_ = newItem;
        }
        head_ = newItem;
        return newItem;
    }


    Item *insert_after(Item *item, Data data)
    {
        if (item)
        {
            Item* newItem = new Item(data, item, item->next());
            if (item->next())
            {
                item->next()->setPrev(newItem);
            }
            else
            {
                tail_ = newItem;
            }
            item->setNext(newItem);
            return newItem;
        }
        else
        {
            return insert(data);
        }
    }

    Item *erase_first()
    {
        if (head_)
        {
            Item* temp = head_;
            head_ = head_->next();
            if (head_)
            {
                head_->setPrev(nullptr);
            }
            else
            {
                tail_ = nullptr;
            }
            delete temp;
        }
        return head_;
    }

    Item *erase_last()
    {
        if (tail_)
        {
            Item* temp = tail_;
            tail_ = tail_->prev();
            if (tail_)
            {
                tail_->setNext(nullptr);
            }
            else
            {
                head_ = nullptr;
            }
            delete temp;
        }
        return tail_;
    }


    Item *erase_next(Item *item)
    {
        if (item && item->next())
        {
            Item* temp = item->next();
            item->setNext(temp->next());
            if (temp->next())
            {
                temp->next()->setPrev(item);
            }
            else
            {
                tail_ = item;
            }
            delete temp;
        }
        return item->next();
    }

private:
    Item* head_;
    Item* tail_;
};

#endif
