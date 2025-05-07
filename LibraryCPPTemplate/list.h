#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List {
    
public:
    
    class Item {
    public:
        Item *next() { return nextItem; }
        Item *prev() { return prevItem; }
        Data& data() { return itemData; } 
        const Data& data() const { return itemData; } 

    private:
        Data itemData;
        Item *nextItem = nullptr;
        Item *prevItem = nullptr;

        friend class List<Data>;
    };

    Item *head;
    size_t listSize;
    List() : head(nullptr), listSize(0) {}

    // Конструктор копирования
    List(const List& other) : head(nullptr), listSize(0) {
        for (Item* current = other.head; current != nullptr; current = current->next()) {
            push_back(current->data());
        }
    }

    // Оператор присваивания
    List& operator=(const List& other) {
        if (this != &other) {
            while (head) {
                erase_first();
            }
            for (Item* current = other.head; current != nullptr; current = current->next()) {
                push_back(current->data());
            }
        }
        return *this;
    }

    ~List() {
        while (head) {
            erase_first();
        }
    }

    void erase(size_t index) {
        if (index >= listSize) return;
    
        Item *current = head;
        Item *prev = nullptr;
    
        for (size_t i = 0; i < index; ++i) {
            prev = current;
            current = current->next();
        }
    
        if (prev) {
            prev->nextItem = current->next();
        } else {
            head = current->next();
        }
    
        if (current->next()) {
            current->next()->prevItem = prev;
        }
    
        delete current;
        --listSize;
    }

    size_t size() const {
        return listSize;
    }

    bool empty() const {
        return head == nullptr;
    }

    Item *get(size_t index) const {
        if (index >= listSize) {
            return nullptr; 
        }
        Item *current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next();
        }
        return current;
    }

    Item *insert(Data data) {
        Item *newItem = new Item();
        newItem->itemData = data;
        newItem->nextItem = head;
        if (head) {
            head->prevItem = newItem;
        }
        head = newItem;
        ++listSize;
        return newItem;
    }

    Item *erase_first() {
        if (!head) return nullptr;
        Item *next = head->next();
        delete head;
        head = next;
        if (head) {
            head->prevItem = nullptr;
        }
        --listSize;
        return head;
    }
    
    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data) {
        Item *newItem = new Item();
        newItem->itemData = data;

        if (!item) {
            newItem->nextItem = head;
            if (head) {
                head->prevItem = newItem;
            }
            head = newItem;
        } else {
            newItem->nextItem = item->next();
            newItem->prevItem = item;
            if (item->next()) {
                item->next()->prevItem = newItem;
            }
            item->nextItem = newItem;
        }

        ++listSize;
        return newItem;

    }

    Item* push_back(const Data& data) {
        Item* newItem = new Item();
        newItem->itemData = data;

        if (!head) {
            head = newItem;
        } else {
            Item* tail = head;
            while (tail->next()) {
                tail = tail->next();
            }
            tail->nextItem = newItem;
            newItem->prevItem = tail;
        }

        ++listSize;
        return newItem;
    }

    Item *erase_next(Item *item) {
        if (!item) {
            return erase_first();
        }

        Item *toDelete = item->next();
        if (!toDelete) return nullptr;

        item->nextItem = toDelete->next();
        if (toDelete->next()) {
            toDelete->next()->prevItem = item;
        }

        delete toDelete;
        --listSize;
        return item->next();
    }    
};

#endif