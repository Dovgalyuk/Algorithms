#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List {
public:
    class Item {
    public:
        Item(Data data) : data_(data), next_(nullptr), prev_(nullptr) {}
        Item* next() { return next_; }
        const Item* next() const { return next_; }
        Item* prev() { return prev_; }
        const Item* prev() const { return prev_; }
        Data& data() { return data_; }
        const Data& data() const { return data_; }
    private:
        Data data_;
        Item* next_;
        Item* prev_;
        friend class List;
    };

    List() : head_(nullptr), tail_(nullptr) {}

    List(const List& a) : head_(nullptr), tail_(nullptr) {
        for (Item* item = a.tail_; item != nullptr; item = item->prev_) {
            insert(item->data_);
        }
    }

    List& operator=(const List& a) {
        if (this != &a) {
            clear();
            for (Item* item = a.tail_; item != nullptr; item = item->prev_) {
                insert(item->data_);
            }
        }
        return *this;
    }

    ~List() {
        clear();
    }

    Item* first() { return head_; }
    const Item* first() const { return head_; }

    Item* insert(Data data) {
        Item* newItem = new Item(data);
        if (head_ == nullptr) {
            head_ = tail_ = newItem;
        } else {
            newItem->next_ = head_;
            head_->prev_ = newItem;
            head_ = newItem;
        }
        return newItem;
    }

    Item* insert_after(Item* item, Data data) {
        if (item == nullptr) {
            return insert(data);
        }
        Item* newItem = new Item(data);
        newItem->next_ = item->next_;
        newItem->prev_ = item;
        if (item->next_ != nullptr) {
            item->next_->prev_ = newItem;
        } else {
            tail_ = newItem;
        }
        item->next_ = newItem;
        return newItem;
    }

    Item* erase_first() {
        if (head_ == nullptr) {
            return nullptr;
        }
        Item* nextItem = head_->next_;
        delete head_;
        head_ = nextItem;
        if (head_ == nullptr) {
            tail_ = nullptr;
        } else {
            head_->prev_ = nullptr;
        }
        return head_;
    }

    Item* erase_next(Item* item) {
        if (item == nullptr || item->next_ == nullptr) {
            return nullptr;
        }
        Item* nextItem = item->next_->next_;
        delete item->next_;
        item->next_ = nextItem;
        if (nextItem != nullptr) {
            nextItem->prev_ = item;
        } else {
            tail_ = item;
        }
        return nextItem;
    }

private:
    Item* head_;
    Item* tail_;

    void clear() {
        while (head_ != nullptr) {
            Item* nextItem = head_->next_;
            delete head_;
            head_ = nextItem;
        }
        tail_ = nullptr;
    }
};

#endif
