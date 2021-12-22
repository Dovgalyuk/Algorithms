#ifndef LIST_H
#define LIST_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item* next() { return nextItem; }
        void new_next_item(Item* newNextItem) { nextItem = newNextItem; }

        Data data() const { return itemData; }

        Item() {
            nextItem = nullptr;
        }

        Item(Data newData, Item* nextItem) {
            itemData = newData;
            this->nextItem = nextItem;
        }

        Item* nextItem;

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
        while (head) {
            Item* temp = head->next();
            delete head;
            head = temp;
        }
    }

    // Retrieves the first item from the list
    Item* first()
    {
        return head;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data)
    {
        head = new Item(data, head);
        return head;
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data)
    {
        item->new_next_item(new Item(data, item->next()));
        return item->next();
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)

    Item* erase(Item* item)
    {
        if (item == head) {
            head = item->next();
            delete item;
            return head;
        }
        else {

            Item* prev_item = head;
            while (prev_item->next() != item) {
                prev_item = prev_item->next();
            }
            prev_item->new_next_item(item->next());
            delete item;
            return prev_item->next();
        }
    }

    // Deletes the list item following the specified one
    // Should be O(1)

    Item* erase_next(Item* item)
    {
        if (item->next() != nullptr) {
            Item* del_item = item->next();
            item->new_next_item(item->next()->next());
            delete del_item;
        }
        return item->next();
    }

private:
    Item* head;
};

#endif