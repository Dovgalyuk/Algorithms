#pragma once
#include <unordered_set>
#include <string>

template <typename hashData, typename Data> class container
{
public:
    class Item
    {
    public:
        Item* nextItem = NULL;

        Item(Data data) : dat(data) {};

        Item* next() { return nextItem; }
        void data(Data i) { dat = i; }
        Data data() { return dat; }
        void hash(hashData i) { hashKey = i; }
        hashData hash() { return hashKey; }
        void Nomer(int i) { index = i; }
        int Nomer() { return index; }

    protected:
        hashData hashKey; //hash
        Data dat; //string
        int index;
    };

    int indexFunction(hashData key)
    {
        if (key % amount < 0) {
            return (key % amount * (-1));
        }
        else {
            return (key % amount);
        }
        
    }

    container(int c)
    {
        this->amount = c;
        firstItem->Nomer(-1);
    }

    ~container()
    {
        Item* item = firstItem;
        while (item->next()) {
            Item* deleted = item;
            item = item->next();
            delete deleted;
        }
        delete item;
    }

    void insert(Data data)
    {
        Item* item = new Item(data);
        item->hash(std::hash<std::string>{}(data));// попробуй hash<Data>
        item->Nomer(indexFunction(item->hash()));
        item->nextItem = NULL;
        if (firstItem->next()) {
            Item* tempItem = firstItem;
            bool checkVstavkiItema = true;
            while (checkVstavkiItema) {
                if (tempItem->next()) {
                    if ((tempItem->next()->Nomer() > item->Nomer()) && ((tempItem->next()->Nomer() - tempItem->Nomer()) >= 2)) {
                        item->nextItem = tempItem->next();
                        tempItem->nextItem = item;
                        checkVstavkiItema = false;
                    }
                    else if (tempItem->next()->Nomer() == item->Nomer()) {
                        if ((tempItem->next()->hash() == item->hash()) && (tempItem->next()->data() == item->data())) {
                            delete item;
                            checkVstavkiItema = false;
                        }
                        else {
                            item->Nomer(item->Nomer() + 1);
                        }
                    }
                    else {
                        tempItem = tempItem->next();
                    }
                }
                else {
                    if (tempItem->Nomer() == amount - 1) {
                        amount = amount * 2;
                        tempItem->nextItem = item;
                        item->Nomer(item->Nomer() + 1);
                        checkVstavkiItema = false;
                    }
                    else {
                        tempItem->nextItem = item;
                        checkVstavkiItema = false;
                    }
                }
            }
        }
        else {
            firstItem->nextItem = item;
        }
    }

    Item* findElement(Data data) {
        Item* tempItem = firstItem;
        while (tempItem->next()) {
            tempItem = tempItem->next();
            if (tempItem->data() == data) {
                return tempItem;
            }
        }
        return NULL;
    }

    void erase(Data data)
    {
        Item* tempItem = firstItem;
        while (tempItem->next()) {
            if (tempItem->next()->data() == data) {
                Item* temp = tempItem->next();
                tempItem->nextItem = tempItem->next()->nextItem;
                delete temp;
                return;
            }
            tempItem = tempItem->next();
        }
    }

    Item* empty() {
        return firstItem ? firstItem : NULL;
    }

protected:
    Item* firstItem = new Item("");
    int amount = 0;
};

