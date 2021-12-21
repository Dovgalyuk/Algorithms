#ifndef LIST_H
#define LIST_H

template <typename Data>
class List {
public:
    class Item {
    public:
        Item *nextItem;
        Item *previousItem;

        Item(Data data) {
            nextItem = nullptr;
            previousItem = nullptr;
            itemData = data;
        }
        Item *next() { return nextItem; }
        Item *prev() { return previousItem; }
        Data data() const { return itemData; }
    private:
        Data itemData;
    };

    // Creates new list
    List() {
        firstItem = nullptr;
    }

    // Destroys the list and frees the memory
    ~List() {
        Item *item = firstItem;
        Item *next;
        while(item != nullptr) {
            next = item->next();
            delete item;
            item = next;
        }
    }

    // Retrieves the first item from the list
    Item *first() {
        return firstItem;
    }

    // Return list items count
    size_t getSize() const {
        int size = 0;
        Item *nextItem = firstItem;
        while(nextItem != nullptr) {
            size++;
            nextItem = nextItem->next();
        }
        return size;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data) {
        auto *newItem = new Item(data);
        newItem->nextItem = firstItem;

        if (firstItem != nullptr)
            firstItem->previousItem = newItem;

        firstItem = newItem;
        return newItem;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data) {
        auto *newItem = new Item(data);
        newItem->nextItem = item->next();

        if (item->next() != nullptr)
            item->next()->previousItem = newItem;

        newItem->previousItem = item;
        item->nextItem = newItem;
        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item) {
        auto *nextItem = item->next();
        auto *prevItem = item->prev();

        if (firstItem == item)
            firstItem = nextItem;

        if (nextItem != nullptr)
            nextItem->previousItem = prevItem;

        if (prevItem != nullptr)
            prevItem->nextItem = nextItem;

        delete item;
        return nextItem;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item) {
        return erase(item->next());
    }
protected:
    Item *firstItem;
};

#endif