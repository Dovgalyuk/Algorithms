#ifndef LIST_H
#define LIST_H

template <typename Data>
class List {
public:
    class Item {
    public:
        Item *next;
        Item *prev;
        Item(Data data) {
            next = nullptr;
            prev = nullptr;
            field = data;
        }

        Item *item_next() { return next; }
        Item *item_prev() { return prev; }

        Data& data() { return field; }
        const Data& data() const { return field; }

    private:    
        Data field;
    };

    // Creates new list
    List() {
        first = nullptr;
    }

    // Destroys the list and frees the memory
    ~List() {
        Item *item = first;
        Item *next;
        while(item != nullptr) {
            next = item->item_next();
            delete item;
            item = next;
        }
    }

    // Retrieves the first item from the list
    Item *list_first() {
        return first;
    }

    // Return list items count
    size_t getSize() const {
        int size = 0;
        Item *next = first;
        while(next != nullptr) {
            size++;
            next = next->next();
        }
        return size;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data) {
        auto newItem = new Item(data);
        newItem->next = first;

        if (first != nullptr)
            first->prev = newItem;

        first = newItem;
        return newItem;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data) {
        auto *newItem = new Item(data);
        newItem->next = item->item_next();

        if (item->item_next() != nullptr)
            item->item_next()->prev = newItem;

        newItem->prev = item;
        item->next = newItem;
        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item) {
        auto *next = item->item_next();
        auto *prevItem = item->item_prev();

        if (first == item)
            first = next;

        if (next != nullptr)
            next->prev = prevItem;

        if (prevItem != nullptr)
            prevItem->next = next;

        delete item;
        return next;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item) {
        return erase(item->item_next());
    }
protected:
    Item *first;
};

#endif
