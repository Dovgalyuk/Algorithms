#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <utility>

template <typename Data>
class List
{
public:
    class Item
    {
        friend class List<Data>;
    private:
        Data data_;
        Item* next_;
        Item* prev_;
        bool is_dummy_;

    public:
        Item(const Data& data = Data(), Item* prev = nullptr, Item* next = nullptr, bool is_dummy = false)
            : data_(data), next_(next), prev_(prev), is_dummy_(is_dummy)
        {
        }

        Item *next()
        {
            if (next_ && next_->is_dummy_)
                return nullptr;
            return next_;
        }

        Item *prev()
        {
            if (prev_ && prev_->is_dummy_)
                return nullptr;
            return prev_;
        }

        const Item *next() const
        {
            if (next_ && next_->is_dummy_)
                return nullptr;
            return next_;
        }

        const Item *prev() const
        {
            if (prev_ && prev_->is_dummy_)
                return nullptr;
            return prev_;
        }

        Data data() const
        {
            return data_;
        }
    };

private:
    Item* dummy_;

public:
    List()
    {
        dummy_ = new Item(Data(), nullptr, nullptr, true);
        dummy_->next_ = dummy_;
        dummy_->prev_ = dummy_;
    }

    List(const List &a)
    {
        dummy_ = new Item(Data(), nullptr, nullptr, true);
        dummy_->next_ = dummy_;
        dummy_->prev_ = dummy_;

        for (Item* curr = a.dummy_->next_; curr != a.dummy_; curr = curr->next_)
        {
            insert_after(last(), curr->data());
        }
    }

    List &operator=(const List &a)
    {
        if (this != &a)
        {
            List copy(a);
            std::swap(dummy_, copy.dummy_);
        }
        return *this;
    }

    ~List()
    {
        Item* curr = dummy_->next_;
        while (curr != dummy_)
        {
            Item* next = curr->next_;
            delete curr;
            curr = next;
        }
        delete dummy_;
    }

    Item *first()
    {
        if (dummy_->next_ == dummy_)
            return nullptr;
        return dummy_->next_;
    }

    Item *last()
    {
        if (dummy_->prev_ == dummy_)
            return nullptr;
        return dummy_->prev_;
    }

    Item *insert(Data data)
    {
        return insert_after(nullptr, data);
    }

    Item *insert_after(Item *item, Data data)
    {
        Item* target = item ? item : dummy_;
        Item* newItem = new Item(data, target, target->next_, false);
        target->next_->prev_ = newItem;
        target->next_ = newItem;
        return newItem;
    }

    Item *erase_first()
    {
        return erase_next(nullptr);
    }

    Item *erase_next(Item *item)
    {
        Item* target = item ? item : dummy_;
        Item* toDelete = target->next_;
        if (toDelete == dummy_)
            return nullptr;

        target->next_ = toDelete->next_;
        toDelete->next_->prev_ = target;

        Item* nextItem = (target->next_ == dummy_) ? nullptr : target->next_;
        delete toDelete;
        return nextItem;
    }
};

#endif