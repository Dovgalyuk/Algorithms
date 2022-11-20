#ifndef LIST_H
#define LIST_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item* nextItem = nullptr;
        Item* prevItem = nullptr;
        Item* next() { return nextItem; }
        Item* prev() { return prevItem; }
        Data data() const { return data_; }
        void setData(Data data_) {
            this->data_ = data_;
        }
    private:
        // internal data here
        Data data_;
    };

    typename List<Data>::Item* lastItem;

    // Creates new list
    List()
    {
        firstItem = nullptr;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        Item* item = firstItem;
        while (item) {
            Item* deletedItem = item;
            item = item->next();
            delete deletedItem;
        }
    }

    // Retrieves the first item from the list
    Item* first()
    {
        return firstItem;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data)
    {
        Item* item = new Item();
        item->setData(data);
        item->nextItem = firstItem;
        if (firstItem) {
            firstItem->prevItem = item;
        }
        firstItem = item;
        return item;
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data)
    {

        Item* newItem = new Item();
        newItem->setData(data);
        newItem->nextItem = item->next();
        item->nextItem = newItem;
        newItem->prevItem = item;
        return newItem;
    }

    // Deletes the specified list item.
    // Returns pointer to the item next to the deleted one.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item* erase(Item* item)
    {

        if (firstItem == item) {
            firstItem = item->next();
        }
        if (item->prev()) {
            item->prev()->nextItem = item->nextItem;
        }
        Item* newItem = item->next();
        delete item;
        return newItem;

    }
    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
private:
    Item* firstItem;
};

#endif


