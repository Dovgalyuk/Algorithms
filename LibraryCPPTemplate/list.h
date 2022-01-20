#ifndef LIST_H
#define LIST_H

template <typename Data>
class List {
public:
    class Item {
    public:
        Item* nextItem;
        Item* previousItem;

        Item(Data data) {
            nextItem = nullptr;
            previousItem = nullptr;
            itemData = data;
        }

        Item* getNext() {
            return nextItem;
        }

        Item* getPrev() {
            return previousItem;
        }

        Data getData() const {
            return itemData;
        }
    private:
        Data itemData;
    };

    // Creates new list
    List() {
        firstItem = nullptr;
    }

    // Destroys the list and frees the memory
    ~List() {
        Item* item = firstItem;
        Item* next;
        while(item != nullptr) {
            next = item->getNext();
            delete item;
            item = next;
        }
    }

    // Retrieves the first item from the list
    Item* first() {
        return firstItem;
    }

    // Return list items count
    size_t getSize() const {
        int size = 0;
        Item *nextItem = firstItem;
        while(nextItem != nullptr) {
            size++;
            nextItem = nextItem->getNext();
        }
        return size;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data) {
        auto *newItem = new Item(data);
        newItem->nextItem = firstItem;

        if (firstItem != nullptr){
            firstItem->previousItem = newItem;
        }


        firstItem = newItem;
        return newItem;
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data) {
        auto *newItem = new Item(data);
        newItem->nextItem = item->getNext();

        if (item->getNext() != nullptr)
            item->getNext()->previousItem = newItem;

        newItem->previousItem = item;
        item->nextItem = newItem;
        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item* erase(Item* item) {
        auto *nextItem = item->getNext();
        auto *prevItem = item->getPrev();

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
    Item* erase_next(Item *item) {
        return erase(item->getNext());
    }
protected:
    Item* firstItem;
};

#endif