#ifndef LIST_H
#define LIST_H
#include <functional>

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return _next; }
        Item *prev() { return _prev; }
        Data data() const { return _data; }
        explicit Item(Data data, Item* next = nullptr, Item* prev = nullptr): _data(data), _next(next), _prev(prev) {}
        void setPrev(Item* item) {_prev = item;}
        void setNext(Item* item) {_next = item;}
    private:
        // internal data here
        Item* _next;
        Item* _prev;
        Data _data;
    };

    // Creates new list
    List()
    {
        fictitious_element = new Item(0);
        fictitious_element->setNext(fictitious_element);
        fictitious_element->setPrev(fictitious_element);
    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item *item;
        while (item)
        {
            item = first();
            if (item == fictitious_element)
                break;
            item->next()->setPrev(item->prev());
            item->prev()->setNext(item->next());

            delete item;

        }

        delete fictitious_element;
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return fictitious_element->next();
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        return insert_after(fictitious_element, data);
    }

    Item *insert_end(Data data)
    {
        Item* newItem = new Item(data);
        newItem->setNext(fictitious_element);
        newItem->setPrev(fictitious_element->prev());
        fictitious_element->prev()->setNext(newItem);
        fictitious_element->setPrev(newItem);

        return newItem;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        Item* newItem = new Item(data);
        newItem->setNext(item->next());
        item->next()->setPrev(newItem);
        newItem->setPrev(item);
        item->setNext(newItem);

        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {

        item->next()->setPrev(item->prev());
        item->prev()->setNext(item->next());
        Item *buff_item = item->next();

        delete item;
        return buff_item;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return nullptr;
    }

    void get_list(){
        Item *num = first();
        while (num != fictitious_element)
        {
            std::cout << num->data() << ' ';
            num = num->next();
        }
    }

    bool empty()
    {
        if (fictitious_element->next() == fictitious_element && fictitious_element->prev() == fictitious_element)
            return true;
        else
            return false;
    }

private:
    // private data should be here

    Item* fictitious_element;
};
#endif