#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <cstddef>
using namespace std;

template <typename Data>
class List {
public:
    class Item {
    public:
        Item(Data data, Item* next = nullptr) : data_(data), next_(next) {}

        Item* next() { return next_; }
        Data& data() { return data_; }
        const Data& data() const { return data_; }

        void setNext(Item* next) { next_ = next; }

    private:
        Data data_;
        Item* next_;
    };

    class const_iterator {
    public:
        const_iterator(Item* current = nullptr) : current_(current) {}

        const_iterator& operator++() {
            if (current_) current_ = current_->next();
            return *this;
        }

        bool operator!=(const const_iterator& other) const {
            return current_ != other.current_;
        }

        const Data& operator*() const {
            return current_->data();
        }

    private:
        Item* current_;
    };

    List() : head_(nullptr), tail_(nullptr), size_(0) {}

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        Item* current = other.head_;
        while (current != nullptr) {
            push_back(current->data());
            current = current->next();
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Item* current = other.head_;
            while (current != nullptr) {
                push_back(current->data());
                current = current->next();
            }
        }
        return *this;
    }

    Item* first() {
        return head_;
    }

    Item* insert(Data data) {
        Item* newItem = new Item(data, head_);
        head_ = newItem;
        if (!tail_) tail_ = head_;
        size_++;
        return newItem;
    }

    Item* insert_after(Item* item, Data data) {
        if (!item) return insert(data);

        Item* newItem = new Item(data, item->next());
        item->setNext(newItem);
        if (item == tail_) tail_ = newItem;
        size_++;
        return newItem;
    }

    Item* erase_first() {
        if (!head_) return nullptr;

        Item* newHead = head_->next();
        delete head_;
        head_ = newHead;
        if (!head_) tail_ = nullptr;
        size_--;
        return head_;
    }

    Item* erase_next(Item* item) {
        if (!item || !item->next()) return nullptr;

        Item* toDelete = item->next();
        Item* newNext = toDelete->next();
        item->setNext(newNext);

        if (toDelete == tail_) tail_ = item;
        delete toDelete;
        size_--;
        return newNext;
    }

    void push_back(Data data) {
        Item* newItem = new Item(data);
        if (!head_) {
            head_ = tail_ = newItem;
        }
        else {
            tail_->setNext(newItem);
            tail_ = newItem;
        }
        size_++;
    }

    void erase(Data data) {
        if (!head_) return;

        if (head_->data() == data) {
            erase_first();
            return;
        }

        Item* current = head_;
        while (current->next()) {
            if (current->next()->data() == data) {
                erase_next(current);
                return;
            }
            current = current->next();
        }
    }

    void clear() {
        while (head_) {
            erase_first();
        }
    }

    const_iterator begin() const { return const_iterator(head_); }
    const_iterator end() const { return const_iterator(nullptr); }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

private:
    Item* head_;
    Item* tail_;
    size_t size_;
};

#endif