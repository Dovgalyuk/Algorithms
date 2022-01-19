#pragma once
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

class container
{
public:
    class Item
    {
    public:

        Item(string data) : dat(data) {};

        void data(string i) { dat = i; }
        string data() { return dat; }
        void hash(int i) { hashKey = i; }
        int hash() { return hashKey; }

    protected:
        int hashKey;
        string dat;
    };

    int indexFunction(int key)
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
        table.resize(amount);
        for (int i = 0; i < amount; i++) {
            table[i] = NULL;
        }
    }

    ~container()
    {
        table.clear();
    }

    void insert(string data)
    {
        Item* item = new Item(data);
        item->hash(hash<string>{}(data));
        if (item->hash() == 0) {
            item->hash(item->hash() + 1);
        }
        int nomerVVectore = indexFunction(item->hash());
        if (table[nomerVVectore] != NULL) {
            bool provercaVstavki = true;
            while (provercaVstavki) {
                nomerVVectore++;
                if (nomerVVectore >= amount) {
                    amountAndTableResize();
                    insert(item->data());
                    return;
                }
                if (table[nomerVVectore] == NULL) {
                    table[nomerVVectore] = item;
                    provercaVstavki = false;
                }
                if (table[nomerVVectore]->hash() == 0) {
                    table[nomerVVectore] = item;
                    provercaVstavki = false;
                }
            }
        }
        else {
            table[nomerVVectore] = item;
        }
    }

    Item* findElement(string data) {
        int index;
        if (hash<string>{}(data) == 0) {
            index = indexFunction(hash<string>{}(data)+1);
        }
        else {
            index = indexFunction(hash<string>{}(data));
        }
        while (index < amount) {
            if (table[index] == NULL) {
                return NULL;
            }
            if (table[index]->data() == data) {
                return table[index];
            }
            index++;
        }
        return NULL;
    }

    bool erase(string data)
    {
        int index;
        if (hash<string>{}(data) == 0) {
            index = indexFunction(hash<string>{}(data)+1);
        }
        else {
            index = indexFunction(hash<string>{}(data));
        }
        while (index < amount) {
            if (table[index] != NULL) {
                if (table[index]->data() == data) {
                    table[index]->data().clear();
                    table[index]->hash(0);
                    return true;
                }
            }
            index++;
        }
        return false;
    }

protected:
    std::vector <Item*> table;
    int amount = 0;

    void amountAndTableResize() {
        amount = amount * 2;
        table.resize(amount);
        for (int i = amount / 2; i < amount; i++) {
            table[i] = NULL;
        }
        for (int i = 0; i < amount / 2; i++) {
            if (table[i] != NULL && table[i]->hash() != 0) {
                string str = table[i]->data();
                delete table[i];
                table[i] = NULL;
                insert(str);
            }
            if (table[i] != NULL && table[i]->hash() == 0) {
                delete table[i];
                table[i] = NULL;
            }
        }
    }
};