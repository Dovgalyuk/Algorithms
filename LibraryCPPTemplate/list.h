#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <initializer_list>
#include <utility>
#include "concepts.h"

template<class Data>
class ListIterator;

template <std::copyable Data>
class List
{
public:
    using value_type = Data;

    class Item
    {
    public:
        Item *next() { return next_; }

        const Item* next() const { return next_; }
        void setNext(Item* nextItem) { next_ = nextItem; }

        const value_type& data() const { return data_; }
        value_type& data() { return data_; }

        explicit Item(value_type item) : data_(item) {}

    private:
        value_type data_;
        Item* next_ = nullptr;
    };

    using iterator = ListIterator<Item*>;
    using const_iterator = ListIterator<const Item*>;

    // Creates new list
    List() = default;

    List(std::initializer_list<value_type> items) {
        auto newItem = head_;
        for (auto& item : items) {
            newItem = insert_after(newItem, item);
        }
    }

    // copy constructor
    List(const List &a)
    {
        Item* head = a.head_;
        for (Item* newItem = head_; head != nullptr; head = head->next()) {
            newItem = insert_after(newItem,head->data());
        }
    }

    List(List&& a)  noexcept {
        head_ = a.head_;
        a.head_ = nullptr;
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this != &a) {
            clear();

            Item* head = a.head_;
            for (Item* newItem = head_; head != nullptr; head = head->next()) {
                newItem = insert_after(newItem,head->data());
            }
        }

        return *this;
    }

    List &operator=(List &&a) noexcept {
        if (this != &a) {
            clear();

            head_ = a.head_;
            a.head_ = nullptr;
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        clear();
    }

    void clear() {
        while (head_) {
            delete std::exchange(head_, head_->next());
        }
    }

    // Retrieves the first item from the list
    Item *first()
    {
        return head_;
    }

    // Inserts new list item into the beginning
    Item *insert(value_type data)
    {
        auto newItem = new Item(data);
        newItem->setNext(head_);
        head_ = newItem;
        return newItem;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, value_type data)
    {
        if (!item) {
            return insert(data);
        }

        auto newItem = new Item(data);
        newItem->setNext(item->next());

        item->setNext(newItem);
        return newItem;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (!head_) {
            return nullptr;
        }
        auto temp = head_;
        head_ = head_->next();
        Item* res = head_;
        delete temp;
        return res;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (!item) {
            return erase_first();
        }
        if (item->next() == nullptr) {
            return nullptr;
        }

        Item* next = item->next();
        Item* afterDel = next->next();
        item->setNext(afterDel);
        delete next;
        return afterDel;
    }

    Item* find(const value_type& data) const noexcept {
        for (auto it = begin(); it != end(); ++it) {
            if (*it == data) {
                return it;
            }
        }

        return nullptr;
    }

    bool empty() const noexcept {
        return head_ == nullptr;
    }

    value_type& front() noexcept {
        return head_->data();
    }

    const value_type& front() const noexcept {
        return head_->data();
    }

    iterator begin() noexcept { return head_; }
    iterator end() noexcept { return nullptr; }
    const_iterator begin() const noexcept { return const_iterator{ head_ } ; }
    const_iterator end() const noexcept { return const_iterator{ nullptr }; }
    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend() const noexcept { return end(); }
private:
    // private data should be here
    Item* head_ = nullptr;
};

template<class Item>
class ListIterator {
public:
    using value_type = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<Item>())>>;

    using difference_type = std::ptrdiff_t;
    using pointer = std::remove_pointer_t<Item>*;
    using reference = std::remove_reference_t<decltype(std::declval<Item>())>;
    using iterator_category = std::forward_iterator_tag;
    using iterator_concept = std::forward_iterator_tag;

    explicit ListIterator(Item itemPtr) noexcept : current_(itemPtr) {}

    reference operator*() const noexcept {
        return current_->data();
    }

    pointer operator->() const noexcept {
        return &current_->data();
    }

    ListIterator& operator++() noexcept {
        current_ = current_->next();
        return *this;
    }

    ListIterator operator++(int) noexcept {
        auto copy = *this;
        current_ = current_->next();
        return copy;
    }

    friend constexpr auto operator<=>(const ListIterator&, const ListIterator&) = default;

private:
    Item current_;
};

#endif
