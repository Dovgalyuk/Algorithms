#ifndef LIST_H
#define LIST_H

#include <cstddef>
typedef int Data;

class List
{
public:
    class Item
    {
    public:
        Item *next() { return next_; }
        Item *prev() { return prev_; }
        Data data() const { return data_; }
    private:
        friend class List;
        Data data_;
        Item *next_;
        Item *prev_;
    };

    List();
    List(const List &a);
    List &operator=(const List &a);
    ~List();
    Item *first();
    const Item *first() const;
    Item *last();
    Item *insert(Data data);
    // A null item means insert at the beginning.
    Item *insert_after(Item *item, Data data);
    Item *erase_first();
    // A null item means erase the first element. Returns the next item.
    Item *erase_next(Item *item);
private:
    Item *first_;
    Item *last_;
};
#endif
