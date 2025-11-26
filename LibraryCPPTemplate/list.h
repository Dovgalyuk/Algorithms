#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List {
public:
    class Item {
    public:
        Item* next() { return nxt; }
        const Item* next() const { return nxt; }
        Item* prev() { return prv; }
        const Item* prev() const { return prv; }
        Data data() const { return dt; }
    private:
        friend class List<Data>;
        Item* nxt = nullptr;
        Item* prv = nullptr;
        Data dt;

        Item(Data val) : nxt(nullptr), prv(nullptr), dt(val) {}
    };

    // Creates new list
    List() : head(nullptr), tail(nullptr) {}

    // copy constructor
    List(const List& a) : head(nullptr), tail(nullptr) {
        Item* cur = a.head;
        while (cur != nullptr) {
            insert(cur->data());
            cur = cur->next();
        }
    }

    // assignment operator
    List& operator=(const List& a) {
        if (this == &a)
            return *this;
        clear();
        Item* cur = a.head;
        while (cur != nullptr) {
            insert(cur->data());
            cur = cur->next();
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List() {
        clear();
    }

    // Retrieves the first item from the list
    Item* first() {
        return head;
    }

    // Const version of first()
    const Item* first() const {
        return head;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data) {
        Item* newItem = new Item(data);
        if (head == nullptr) {
            head = tail = newItem;
        }
        else {
            newItem->nxt = head;
            head->prv = newItem;
            head = newItem;
        }
        return newItem;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item* insert_after(Item* item, Data data) {
        if (item == nullptr) {
            return insert(data);
        }
        Item* newItem = new Item(data);
        newItem->prv = item;
        newItem->nxt = item->nxt;
        if (item->nxt != nullptr) {
            item->nxt->prv = newItem;
        }
        item->nxt = newItem;
        if (item == tail) {
            tail = newItem;
        }
        return newItem;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item* erase_first() {
        if (head == nullptr)
            return nullptr;
        Item* toDelete = head;
        head = head->nxt;
        if (head != nullptr)
            head->prv = nullptr;
        else
            tail = nullptr;
        Item* nextItem = head;
        delete toDelete;
        return nextItem;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    Item* erase_next(Item* item) {
        if (item == nullptr) {
            // Erase first
            return erase_first();
        }
        Item* toDelete = item->nxt;
        if (toDelete == nullptr)
            return nullptr;
        item->nxt = toDelete->nxt;
        if (toDelete->nxt != nullptr) {
            toDelete->nxt->prv = item;
        }
        else {
            tail = item;
        }
        Item* nextItem = toDelete->nxt;
        delete toDelete;
        return nextItem;
    }

private:
    Item* head;
    Item* tail;

    void clear() {
        while (head != nullptr) {
            erase_first();
        }
    }
};

#endif