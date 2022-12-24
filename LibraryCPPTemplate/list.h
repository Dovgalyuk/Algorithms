#ifndef LIST_H
#define LIST_H

template <typename Data>
class List {
public:
    class Item {
    public:
        Item* nextt;
        Item* prevv;
        Item(Data data) {
            nextt = nullptr;
            prevv = nullptr;
            field = data;
        }

        Item* next() { return nextt; }
        Item* prev() { return prevv; }
        Data& data() { return field; }
        const Data& data() const { return field; }

    private:
        Data field;
    };

    // Creates new list
    List() {
        head = nullptr;
    }

    // Destroys the list and frees the memory
    ~List() {
        Item* item = head;
        Item* nextItem;
        while (item != nullptr) {
            nextItem = item->next();
            delete item;
            item = nextItem;
        }
    }

    // Retrieves the first item from the list
    Item* first() {
        return head;
    }

    // Return list items count
    size_t getSize() const {
        int size = 0;
        Item* next = head;
        while (next != nullptr) {
            size++;
            next = next->next();
        }
        return size;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data) {
        auto newItem = new Item(data);
        newItem->nextt = head;

        if (head != nullptr)
            head->prevv = newItem;

        head = newItem;
        return newItem;
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data) {
        auto* newItem = new Item(data);
        newItem->nextt = item->next();

        if (item->next() != nullptr)
            item->next()->prevv = newItem;

        newItem->prevv = item;
        item->nextt = newItem;
        return newItem;
    }

    // Deletes the specified list item.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item* erase(Item* item) {
        auto* nextItem = item->next();
        auto* prevItem = item->prev();

        if (head == item)
            head = nextItem;

        if (nextItem != nullptr)
            nextItem->prevv = prevItem;

        if (prevItem != nullptr)
            prevItem->nextt = nextItem;

        delete item;
        return nextItem;
    }

    // Deletes the list item following the specified one
    // Should be O(1)
    Item* erase_next(Item* item) {
        return erase(item->next());
    }
protected:
    Item* head;
};

#endif
