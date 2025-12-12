#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item *next() { return mNext; }
        Item *prev() { return nullptr; }
        Data data() const { return mData; }
    private:
        
        friend class List<Data>;

        Item *mNext = nullptr;
        Data mData;

        Item(Data data, Item *next = nullptr) 
        {
            mData = data;
            mNext = next;
        }

    };

    // Creates new list
    List()
    {
        mHead = nullptr;
    }

    // copy constructor
    List(const List &a)
    {
        mHead = nullptr;
        if (a.mHead == nullptr) return;

        mHead = new Item(a.mHead->mData);
        Item* current = mHead;
        Item* source = a.mHead->mNext;

        while (source != nullptr) {
            current->mNext = new Item(source->mData);
            current = current->mNext;
            source = source->mNext;
        }
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this != &a) {

            while (mHead != nullptr) {
                Item *temp = mHead;
                mHead = mHead->mNext;
                delete temp;
            }

            if (a.mHead) {
                mHead = new Item(a.mHead->mData);
                Item* current = mHead;
                Item* source = a.mHead->mNext;

                while (source) {
                    current->mNext = new Item(source->mData);
                    current = current->mNext;
                    source = source->mNext;
                }
            }
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while (mHead != nullptr) {
            Item *temp = mHead;
            mHead = mHead->mNext;
            delete temp;
        }
    }

    // Retrieves the first item from the list
    Item *first() const
    {
        return mHead;
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        Item *newItem = new Item(data, mHead);
        mHead = newItem;
        return newItem;
    }

    // Inserts new list item after the specified item
    // Inserts first element if item is null
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr) {
            return insert(data);
        }

        Item *newItem = new Item(data, item->mNext);
        item->mNext = newItem;
        
        return newItem;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (mHead == nullptr) return nullptr;

        Item *temp = mHead;
        Item *nextItem = mHead->mNext;
        
        mHead = nextItem;
        delete temp;
        
        return nextItem;
    }

    // Deletes the list item following the specified one.
    // Deletes the first element when item is null.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == nullptr) {
            return erase_first();
        }

        if (item->mNext == nullptr) {
            return nullptr;
        }

        Item *toDelete = item->mNext;
        Item *nextAfterDeleted = toDelete->mNext;

        item->mNext = nextAfterDeleted;
        delete toDelete;

        return nextAfterDeleted;
    }
private:
    // private data should be here
    Item *mHead;
};

#endif
