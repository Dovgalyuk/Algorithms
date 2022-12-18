#ifndef LIST_H
#define LIST_H

#include <cstdio>

template <typename Data> 
class List
{
public:
    class Item
    {
    public:

        Item(Data data = NULL, Item* next = nullptr) {
            this->next = next;
            this->data = data;
        }

        void setData(Data data) {
            this->data = data;
        }
        void setNext(Item* next) {
            this->next = next;
        }

        Data getData() {
            return this->data;
        }
        Item* getNext() {
            return this->next;
        }

    private:
        Item* next;
        Data data;
    };

    // Creates new list
    List()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->listSize = 0;
    }

    //// copy constructor
    //List(const List& a)
    //{
    //    // implement or disable this function
    //}

    //// assignment operator
    //List& operator=(const List& a)
    //{
    //    // implement or disable this function
    //    return *this;
    //}

    // Destroys the list and frees the memory
    ~List()
    {
        while (head) {
            Item* temp_head = head;
            head = head->getNext();
            delete temp_head;
        }
    }

    // Retrieves the first item from the list
    Item* first()
    {
        return head;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data)
    {
        this->listSize++;
        if (head != nullptr) return head = new Item(data, head);
        else {
            head = new Item(data);
            tail = head;
            return head;
        }
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data)
    {
        this->listSize++;
        if (item->getNext() == nullptr) {
            tail = new Item(data);
            item->setNext(tail);
            return tail;
        }
        else {
            Item* temp_item = new Item(data, item->getNext());
            item->setNext(temp_item);
            return temp_item;
        }
    }

    // Deletes the specified list item.
    // Returns pointer to the item next to the deleted one.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item* erase(Item* item)
    {
        this->listSize--;
        if (head == nullptr) throw "List is empty";
        else if (item == head) {

            if (item == tail) {
                tail = nullptr;
            }

            head = item->getNext();
            delete item;
            return head;
        }
        else if (item == tail) {
            Item* temp_item = head;
            for (int i = 0; i <= listSize; i++)
            {
                temp_item = temp_item->getNext();
                if (i == listSize) {
                    delete item;
                    return tail = temp_item;
                }
            }
        } 
        else {
            Item* temp_prev = head;
            Item* temp_item = temp_prev->getNext();
            
            while (temp_item != item) {
                Item* temp_prev = head->getNext();
                Item* temp_item = temp_prev->getNext();
            }

            temp_prev->setNext(item->getNext());
            delete item;
            return temp_prev->getNext();
        }
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item* erase_next(Item* item)
    {
        if (head==nullptr || item->getNext == nullptr) throw "Error! You type wrong item";
        else {
            return erase(item->getNext);
        }
    }

private:
    Item* head, *tail;
    size_t listSize;
};

#endif