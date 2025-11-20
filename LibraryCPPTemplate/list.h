#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item(Data data, Item* next = nullptr): data_i(data), next_i(next){}

        Item *next() 
        { 
            return next_i; 
        }

        Data data() const 
        { 
            return data_i; 
        }

        void setNext(Item* next) 
        {
            next_i = next;
        }

    private:
        Data data_i;
        Item* next_i; 
    };

    List(): head(nullptr){}

    List(const List &a) : head(nullptr)
    {
        Item* current = a.head;

        while (current != nullptr) 
        {
            insert(current->data());
            current = current->next();
        }
    }

    List &operator=(const List &a)
    {
        if (this != &a) 
        {
            clear();

            Item* current = a.head;

            while (current != nullptr)  
            {
                insert(current->data());
                current = current->next();
            }
        }

        return *this;
    }

    ~List()
    {
        clear();
    }

    Item *first()
    {
        return head;
    }

    Item *insert(Data data)
    {
        Item* newItem = new Item(data, head);
        head = newItem;

        return newItem;
    }

    Item *insert_after(Item *item, Data data)
    {
        if(item == nullptr)
        {
            return insert(data);
        }
        
        Item* newItem = new Item(data, item->next());
        item->setNext(newItem);

        return newItem;
    }

    Item *erase_first()
    {
        if(head == nullptr)
        {
            return nullptr;
        }

        Item* next = head->next();
        delete head;
        head = next;

        return head;
    }

    Item *erase_next(Item *item)
    {
        if(item == nullptr)
        {
            return erase_first();
        }

        Item* deletes = item->next();

        if(deletes == nullptr)
        {
            return nullptr;
        }

        Item* next = deletes->next();
        item->setNext(next);
        delete deletes;

        return next;
    }

    void clear()
    {
        while(head != nullptr)
        {
            Item* next = head->next();
            delete head;
            head = next;
        }
    }

private:
    Item* head;
};

#endif
