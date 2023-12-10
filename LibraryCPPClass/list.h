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
      Data& data() { return itemData; }
      Item*& next() { return nextItem; }
   private:
      Data itemData;
      Item *nextItem;
   };
   List();
   List(const List &a);
   List &operator=(const List &a);
   ~List();

   Item *first() const;
   Item *insert(Data data);
   Item *insert_after(Item *item, Data data);
   Item *erase_first();
   Item *erase_next(Item *item);

private:
   Item* head;
};

#endif
