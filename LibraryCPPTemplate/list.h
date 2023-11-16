#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#ifdef __GNUC__
#define FUNCTION_CALLER() __builtin_FUNCTION()
#endif

#ifndef FUNCTION_CALLER
#define FUNCTION_CALLER() "(impossible to get caller not in GCC)"
#endif

#include <functional>
#include <exception>
#include <stdexcept>
#include <string>
#include <initializer_list>

class ListException;

template <typename Data>
class List
{
public:
    class Item
    {
    public:
        Item *next() { return iNext; }
        // Item *prev() { return nullptr; } // Doubly linked list
        Data data() const { return iData; }

        Item(Data data) : iData(data) {}

        Item(Data data, Item *next) : iData(data), iNext(next) {}

    private:
        Data iData;
        Item *iNext;
        // internal data here
    };

    // Creates new list
    List() : mFirst(nullptr), mLast(nullptr), mSize(0) {}

    // Constructor with initializer list;
    List(std::initializer_list<Data> l) : List()
    {
        for (auto it = l.begin(); it != l.end(); it++)
        {
            if (it == l.begin())
                insert(*it);
            else
                insert_after(mLast, *it);
        }
    }

    // Creates and fill list with size and functions result on each iteration
    List(std::size_t size, std::function<Data(std::size_t)> filler) : List()
    {
        if (size > 1)
            append(size, filler);
    }

    // Copy constructor
    List(const List<Data> &a) : List()
    {
        if (a.mSize > 0)
        {
            Item *iterator = a.mFirst;
            insert(iterator->data());
            while (mSize < a.mSize)
            {
                iterator = iterator->next();
                insert_after(mLast, iterator->data());
            }
        }
    }

    // Assignment operator
    List &operator=(const List<Data> &a)
    {
        if (a.mSize < 1)
            clear();
        else
        {
            Item *iteratorA = a.mFirst;
            Item *iteratorM = mFirst;
            if (mSize == 0)
            {
                insert(iteratorA->data());
                iteratorM = mFirst;
            }
            while (iteratorA != nullptr)
            {
                *iteratorM = Item(iteratorA->data(), iteratorM->next());
                if (iteratorM->next() == nullptr && iteratorA->next() != nullptr)
                    insert_after(iteratorM, iteratorA->data());
                iteratorM = iteratorM->next();
                iteratorA = iteratorA->next();
            }
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while (mSize > 0)
            erase_first();
    }

    // Retrieves size of list
    std::size_t size() { return mSize; }

    // Checks if list is empty
    bool empty() const { return mSize == 0; }

    // Retrieves the first item from the list
    Item *first() const { return mFirst; }

    // Retrieves the last item from the list
    Item *last() const { return mLast; }

    // Checks if item with specified data contains in list
    bool contains(Data data)
    {
        Item *iterator = mFirst;
        while (iterator != nullptr)
        {
            if (iterator->data() == data)
                return true;
            iterator = iterator->next();
        }
        return false;
    }

    // Find item with specified date and return its index, if such item does not exists returns -1.
    std::size_t indexOf(Data data)
    {
        std::size_t index = 0;
        Item *iterator = mFirst;
        while (iterator != nullptr)
        {
            if (iterator->data() == data)
                return index;
            iterator = iterator->next();
            index++;
        }
        throw ListException("item with specified data does not exists");
    }

    // Inserts new list item into the beginning
    Item *insert(Data data)
    {
        mFirst = new Item(data, mFirst);

        if (mLast == nullptr)
            mLast = mFirst;

        mSize++;
        return mFirst;
    }

    // Inserts new list item after the specified item
    Item *insert_after(Item *item, Data data)
    {
        if (item == nullptr)
            throw ListException("item is nullptr");

        Item *insert = new Item(data, item->next());

        *item = Item(item->data(), insert);

        if (item == mLast)
            mLast = insert;

        mSize++;

        return insert;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item *erase_first()
    {
        if (mSize == 0)
            throw ListException("list is empty");

        Item *second = mFirst->next();
        delete mFirst;
        mFirst = second;

        if (mFirst == nullptr)
            mLast = nullptr;

        mSize--;

        return mFirst;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item *erase_next(Item *item)
    {
        if (item == mLast)
            throw ListException("this item is last");

        if (item->next() == mLast)
        {
            delete item.next();

            mLast = item;

            *item = Item(item.data(), nullptr);
        }
        else
        {
            Item *toDelete = item.next();

            *item = Item(item.data(), toDelete.next());

            delete toDelete;
        }
        mSize--;
        return item;
    }

    // Increases size, inserts need count of items at the end with specified filler.
    void append(std::size_t count, std::function<Data(std::size_t)> filler)
    {
        if (count < 1)
            return;

        if (mLast == nullptr)
        {
            insert(filler(mSize));
            count--;
        }
        while (count > 0)
        {
            insert_after(mLast, filler(mSize));
            count--;
        }
    }

    // Increases size, inserts need count of items at the start with specified filler.
    void appendStart(std::size_t count, std::function<Data(std::size_t)> filler)
    {
        if (count < 1)
            return;

        while (count > 0)
        {
            insert(filler(count - 1));
            count--;
        }
    }

    // Drops at the start specified count of items.
    void drop(std::size_t count)
    {
        if (count < 1)
            throw ListException("count of items must be positive");

        while (count > 0)
        {
            erase_first();
            count--;
        }
    }

    // Erases all items.
    void clear()
    {
        while (mSize > 0)
            erase_first();
    }

private:
    // private data should be here
    Item *mFirst;
    Item *mLast;
    std::size_t mSize;
};

class ListException : public std::runtime_error
{

public:
    ListException(std::string message, std::string caller = FUNCTION_CALLER()) : std::runtime_error(caller + "(): " + message) {}
};

#endif
