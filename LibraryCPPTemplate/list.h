#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List
{
public:
    class Item
    {
        friend class List<Data>;
    public:
        Item* next() { return next_; }
        Item* prev() { return prev_; }
        Data data() const { return data_; }

    private:
        Data data_;
        Item* next_;
        Item* prev_;
        Item(const Data& d) : data_(d), next_(nullptr), prev_(nullptr) {}
    };

    // Creates new list
    List() : head_(nullptr), tail_(nullptr) {}

    // copy constructor
    List(const List& other) : head_(nullptr), tail_(nullptr)
    {
        Item* current = other.head_;
        while (current) {
            // Вставляем в конец: если список пуст — insert, иначе insert_after(tail_)
            if (!head_) {
                insert(current->data_);
            }
            else {
                insert_after(tail_, current->data_);
            }
            current = current->next_;
        }
    }
}

    // assignment operator
List& operator=(const List& other)
{
    if (this == &other) return *this;

    // Очистка
    while (head_) {
        Item* tmp = head_;
        head_ = head_->next_;
        delete tmp;
    }
    tail_ = nullptr;

    // Копирование в правильном порядке
    Item* current = other.head_;
    while (current) {
        if (!head_) {
            insert(current->data_);
        }
        else {
            insert_after(tail_, current->data_);
        }
        current = current->next_;
    }
    return *this;
}}

    // Destroys the list and frees the memory
    ~List()
    {
        while (head_) {
            Item* tmp = head_;
            head_ = head_->next_;
            delete tmp;
        }
    }

    // Retrieves the first item from the list
    Item* first()
    {
        return head_;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data)
    {
        Item* newItem = new Item(data);
        if (!head_) {
            head_ = tail_ = newItem;
        }
        else {
            newItem->next_ = head_;
            head_->prev_ = newItem;
            head_ = newItem;
        }
        return newItem;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item* insert_after(Item* item, Data data)
    {
        if (!item) {
            return insert(data);
        }
        Item* newItem = new Item(data);
        newItem->next_ = item->next_;
        newItem->prev_ = item;
        if (item->next_) {
            item->next_->prev_ = newItem;
        }
        else {
            tail_ = newItem; // item was tail
        }
        item->next_ = newItem;
        return newItem;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item* erase_first()
    {
        if (!head_) return nullptr;
        Item* nextItem = head_->next_;
        delete head_;
        if (nextItem) {
            nextItem->prev_ = nullptr;
            head_ = nextItem;
        }
        else {
            head_ = tail_ = nullptr;
        }
        return nextItem;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item* erase_next(Item* item)
    {
        if (!item) {
            return erase_first();
        }
        if (!item->next_) {
            return nullptr;
        }
        Item* toErase = item->next_;
        Item* nextNext = toErase->next_;
        item->next_ = nextNext;
        if (nextNext) {
            nextNext->prev_ = item;
        }
        else {
            tail_ = item; // toErase was tail
        }
        delete toErase;
        return nextNext;
    }

private:
    Item* head_;
    Item* tail_;
};

#endif // LIST_TEMPLATE_H