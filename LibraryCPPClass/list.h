#ifndef LIST_H
#define LIST_H

typedef int Data;

class List {
   public:
    class Item {
       public:
        Item* next();
        const Item* next() const;
        Item* prev();
        const Item* prev() const;
        Data data() const;

       private:
        friend class List;

        Item();
        Item(Data data, Item* prev, Item* next);

        Data data_;
        Item* next_;
        Item* prev_;
        bool is_dummy_;
    };

    List();
    List(const List& a);
    List& operator=(const List& a);
    ~List();

    Item* first();
    const Item* first() const;
    Item* last();
    const Item* last() const;

    Item* insert(Data data);
    Item* insert_after(Item* item, Data data);

    Item* erase_first();
    Item* erase_next(Item* item);

   private:
    Item* dummy_;
};

#endif