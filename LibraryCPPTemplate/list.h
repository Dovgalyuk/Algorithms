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
        lastItem = nullptr;
        size = 0;
    }

    // Destroys the list and frees the memory
    ~List() {
        while(firstItem != nullptr) {
            auto *item = firstItem;
            firstItem = item->next();
            delete item;
        }
    }

    // Retrieves the first item from the list
    Item *first() {
        return firstItem;
    }

    // Retrieves the last item from the list
    Item *last() {
        return lastItem;
    }

    // Return list items count
    size_t getSize() const {
        return size;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data) {
        auto *newItem = new Item(data);
        newItem->nextItem = firstItem;
        if (firstItem != nullptr) {
            firstItem->previousItem = newItem;
        } else lastItem = newItem;
        firstItem = newItem;
        size++;
        return newItem;
    }

    // Костыль, т.к. из-за использований шаблонов сделать виртуальный метод insert нельзя
    // и я к сожалению не знаю как это правильно обойти
    void ins(Data data) {
        insert(data);
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data) {
        auto *newItem = new Item(data);
        newItem->nextItem = item->next();
        item->nextItem = newItem;
        newItem->previousItem = item;
        if (item->next() != nullptr) {
            item->next()->previousItem = newItem;
        }
        size++;
        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item *erase(Item *item) {
        auto *nextItem = item->next();

        if (firstItem == item)
            firstItem = nextItem;

        if (lastItem == item)
            lastItem = item->prev();

        if (item->next() != nullptr)
            item->next()->previousItem = item->prev();

        if (item->prev() != nullptr)
            item->prev()->nextItem = item->next();

        delete item;
        size--;
        return nextItem;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item *erase_next(Item *item) {
        return erase(item->next());
    }
private:
    Item *firstItem;
    Item *lastItem;

    size_t size;
};

#endif
