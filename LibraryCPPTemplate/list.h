#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Item(Data val) : inf(val), next_ptr(nullptr), prev_ptr(nullptr) {}

        Item *next()
        {
            return next_ptr;
        }

        Item *prev()
        {
            return prev_ptr;
        }

        Data data() const
        {
            return inf;
        }

    private:
        Data inf;
        Item *next_ptr;
        Item *prev_ptr;

        friend class List;
    };

    List()
    {
        first_ptr = nullptr;
        last_ptr = nullptr;
    }

    List(const List &a) : List()
    {
        Item *item = a.first_ptr;
        while (item != nullptr)
        {
            insert_after(last_ptr, item->inf);
            item = item->next_ptr;
        }
    }

    List &operator=(const List &a)
    {
        if (this != &a)
        {
            List tmp(a);

            Item *tmp_first = first_ptr;
            Item *tmp_last = last_ptr;

            first_ptr = tmp.first_ptr;
            last_ptr = tmp.last_ptr;

            tmp.first_ptr = tmp_first;
            tmp.last_ptr = tmp_last;
        }
        return *this;
    }

    ~List()
    {
        while (first_ptr != nullptr)
        {
            erase_first();
        }
    }

    Item *first() const
    {
        return first_ptr;
    }

    Item *last() const
    {
        return last_ptr;
    }

    Item *insert(Data data)
    {
        Item *new_item = new Item(data);
        new_item->next_ptr = first_ptr;
        if (first_ptr != nullptr)
        {
            first_ptr->prev_ptr = new_item;
        }
        if (last_ptr == nullptr)
        {
            last_ptr = new_item;
        }
        first_ptr = new_item;

        return new_item;
    }

    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr)
        {
            return insert(data);
        }
        Item *new_item = new Item(data);

        new_item->prev_ptr = item;
        new_item->next_ptr = item->next_ptr;

        if (item->next_ptr != nullptr)
        {
            item->next_ptr->prev_ptr = new_item;
        }
        else
        {
            last_ptr = new_item;
        }
        item->next_ptr = new_item;

        return new_item;
    }

    Item *erase_first()
    {
        if (first_ptr == nullptr)
        {
            return nullptr;
        }

        Item *new_item = first_ptr->next_ptr;

        if (new_item != nullptr)
        {
            new_item->prev_ptr = nullptr;
        }
        else
        {
            last_ptr = nullptr;
        }

        delete first_ptr;
        first_ptr = new_item;

        return first_ptr;
    }

    Item *erase_next(Item *item)
    {
        if (item == nullptr)
        {
            return erase_first();
        }

        Item *delete_item = item->next_ptr;
        if (delete_item == nullptr)
        {
            return nullptr;
        }

        Item *after_delete = delete_item->next_ptr;

        if (after_delete != nullptr)
        {
            after_delete->prev_ptr = item;
        }
        else
        {
            last_ptr = item;
        }

        item->next_ptr = after_delete;

        delete delete_item;
        return after_delete;
    }

private:
    Item *first_ptr;
    Item *last_ptr;
};

#endif
