
#ifndef LIST_H
#define LIST_H

typedef int Data;

class List
{
public:
    class Item
    {
    public:
        Item *next() { return next_; }
        Item *prev() { return prev_; }
        Data data() const { return value_; }

    private:
        Data value_;
        Item *next_;
        Item *prev_;

        explicit Item(Data value) : value_(value), next_(nullptr), prev_(nullptr) {}
        friend class List;
    };

    List();
    List(const List &a);
    List &operator=(const List &a);
    ~List();

    Item *first();
    const Item *first() const;
    Item *last();

    Item *insert(Data data);
    Item *insert_after(Item *item, Data data);
    Item *erase_first();
    Item *erase_next(Item *item);

private:
    Item *head_;
    Item *tail_;
};

#endif
