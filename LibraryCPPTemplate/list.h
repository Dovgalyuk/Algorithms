#ifndef LIST_H
#define LIST_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return nextItem; }
        void next(Item *newNextItem) {nextItem = newNextItem;}
        //Item *prev() { return nullptr; }
        Data data() const { return itemData; }

        Item() {
            nextItem = nullptr;
        }
        Item(Data newData, Item *nextItem) {
            itemData = newData;
            this->nextItem = nextItem;
        }
        Item *nextItem;
    private:
        Data itemData;
        
    };

    // Creates new list
    List()
    {
        head = nullptr;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while(head) {
            Item* temp = head->next();
            delete head;
            head = temp;
        }
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return head;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        head = new Item(data, head);
        return head;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        item->next(new Item(data, item->next()));
        return item->next();
    }
    
    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item)
    {
        if(item == head) {
            
            head = item->next();
            
            delete item;
            return head;
        } else {
            Item *cur = head;
            while (cur->next() != item) {
                cur = cur->next();
            }
            cur->next(cur->next()->next());
            delete item;
            return cur->next();
        }
        
        
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item->next()) {
            Item *mustBeDeleted = item->next();
            item->next(item->next()->next());
            delete mustBeDeleted
        }
        return item->next();
    }
private:
    Item *head;
};

#endif
