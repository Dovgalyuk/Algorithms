#ifndef LIST_H
#define LIST_H

typedef int Data;

class List {
public:
    class Item {
    public:
        Item* next() {
            if (nextItem != nullptr && nextItem->isDummy) return nullptr;
            return nextItem;
        }
        Item* prev() {
            if (prevItem != nullptr && prevItem->isDummy) return nullptr;
            return prevItem;
        }
        Data data() const { return itemData; }
    private:
        Data itemData;
        Item* nextItem;
        Item* prevItem;
        bool isDummy;
        friend class List;
    };

    List();
    List(const List& a);
    List& operator=(const List& a);
    ~List();

    Item* first() const;
    Item* last() const;
    Item* insert(Data data);
    Item* insert_after(Item* item, Data data);
    Item* erase_first();
    Item* erase_next(Item* item);
private:
    Item* dummy;
};

#endif
