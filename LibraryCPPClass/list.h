#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <stdexcept>

typedef int Data;

class List
{
public:
    class Item
    {
    public:
        Item(Data data, Item* next = nullptr)
            : data_(data), next_(next) {}

        Item* next() const { return next_; }
        void set_next(Item* next) { next_ = next; } // Устанавливаем значение next_
        Data data() const { return data_; }

    private:
        Data data_;
        Item* next_;
    };

    List() : head_(nullptr) {}

    List(const List& a);
    List& operator=(const List& a);

    ~List();

    Item* first() const { return head_; }
    Item* insert(Data data);
    Item* insert_after(Item* item, Data data);
    Item* erase_first();
    Item* erase_next(Item* item);

private:
    Item* head_;
};

#endif
