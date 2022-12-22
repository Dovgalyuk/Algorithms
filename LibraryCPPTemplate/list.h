#ifndef LIST_H
#define LIST_H

template <typename Data> 
class List
{
public:
    class Item
    {
    public:
        Item* nextt;
        Item* prevv;
        Item(Data data)
        {
            nextt = nullptr;
            prevv = nullptr;
            field = data;
        }
        Item* next() {return nextt;}
        Item* prev() {return prevv;}
        Data& data() {return field;}
        const Data& data() const {return field;}

    private:
        Data field;
    };

    // Creates new list
    List()
    {
        head = nullptr;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item* item = head;
        Item* next;
        while (item != nullptr) {
            next = item->next();
            delete item;
            item = next;
        }
    }

    // Retrieves the head item from the list
    Item *first()
    {
        return head;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        auto newItem = new Item(data);
        newItem->nextt = head;
        if (head != nullptr)
        {
            head->prevv = newItem;
        }
        head = newItem;
        return newItem;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        auto* newItem = new Item(data);
        newItem->nextt = item->next();
        newItem->prevv = item;
        if (item->next() != nullptr)
        {
            item->next()->prevv = newItem;
        }
        item->nextt = newItem;
        return newItem;
    }

    // Deletes the specified list item.
    // Returns pointer to the item next to the deleted one.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        auto *nextItem = item->next();
        auto *prevItem = item->prev();

        if (head == item)
        {
            head = nextItem;
        }
        if (nextItem != nullptr)
        {
            prevItem = nextItem->prev();
        }
        if (prevItem != nullptr)
        {
            nextItem = prevItem->next();
        }
        delete item;
        return nextItem;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        return erase(item->next());
    }

    size_t get_size() const {
        int size = 0;
        Item* nextItem = head;
        while (nextItem != nullptr) {
            size++;
            nextItem = nextItem->next();
        }
        return size;
    }
protected:
    Item* head;
};

#endif
