#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return this->_next; }
        Item *prev() { return this->_prev; }
        Data data() const { return this->field; }


        Item()
        {

        }

        Item(Data data, Item* next, Item* prev)
        {
            this ->_next = next;
            this->_prev = prev;
            this -> field = data;
        }

        void set_next(Item* item) //fix C2106
        {
            this->_next = item;
        }

        void set_prev(Item* item)
        {
            this->_prev = item;
        }

    private:
        // internal data here
        Data field;
        Item* _next;
        Item* _prev;
    };

    // Creates new list
    List()
    {
        this->Head = nullptr;
    }

    // copy constructor
    template <typename T>
    List(const List<T> &a)
    {
        Item* it = a->Head;

        this->Head = new Item(it.data(), nullptr, nullptr);

        Item* past_p, * p;

        p = nullptr;
        past_p = this->Head;

        it = it.next();

        while (it != nullptr)
        {
            p = new Item(it.data(), nullptr, nullptr);
            past_p->next() = p;
            p->prev() = past_p;

            p = p->next();
            past_p = past_p->next();
            it = it->next();
        }

     /*   Item* _this = this->Head;
        Item* _other = a->Head;
        Item* past_this;

        if (a == nullptr)
        {
            if (this->Head == nullptr) return;

            else
            {
                delete this->Head;
                this->Head = nullptr;
            }
        }

        while (_other != nullptr)
        {
            if (_this == nullptr)
            {
                _this = new Item(_other.data(), past_this, nullptr);
            }
            else
            {
                _this->data() = _other.data();
            }

            _this = _this->next();
            _other = _other->next();
        }*/
    }

    // assignment operator
    template <typename T>
    List &operator=(const List<T> &a)
    {
        if (this->Head != nullptr)
        {
            delete this->Head;
        }

        Item* it = a->Head;

        this->Head = new Item(it.data(), nullptr, nullptr);

        Item* past_p, * p;

        p = nullptr;
        past_p = this->Head;

        it = it.next();

        while (it != nullptr)
        {
            p = new Item(it.data(), nullptr, nullptr);
            past_p->next() = p;
            p->prev() = past_p;

            p = p->next();
            past_p = past_p->next();
            it = it->next();
        }
    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item *current = this->Head->next();
        while (current != nullptr)
        {
            Item* next = current->next();
            delete current;
            current = next;
            
        }

        delete this->Head;
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return this -> Head;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item* old_Head;

        if (this->Head != nullptr)
        {
            old_Head = this->Head;
            this->Head = new Item{ data, old_Head, nullptr };
            old_Head->set_prev(this->Head);
        }
        else
        {
            this->Head = new Item{ data, nullptr, nullptr };
        }

        return this->Head;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr || this->Head == nullptr) return nullptr;

        Item* new_item = new Item{ data, item->next(), item };

        item->set_next(new_item);

        item = item->next()->next();

        item->set_prev(new_item);

        return new_item;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        Item *p = this -> Head;

        this->Head = this->Head->next();

        delete p;

        return this -> Head;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == nullptr || item->next == nullptr || this->Head == nullptr)
            return nullptr;

        Item* p;
        p = item->next();
        item->next() = p->next();

        delete p;
        return item->next(); //maybe return nullptr
    }
private:
    // private data should be here
    Item* Head;
};

#endif
