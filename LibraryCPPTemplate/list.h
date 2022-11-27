#ifndef LIST_H
#define LIST_H
#include <cstdio>

template <typename Data>
class List{
public:
    class Item{
    public:
        Item* next_item;
        Item* prev_item;

        Item(Data data, Item* next) {
            this->item_data= data;
            this->next_item = next;
        }
        
        Data data() { return this->item_data; }
        Item* next() { return this->next_item; }
        Item* prev() { return this->prev_item; }
        void setData(Data data) { this->data = data; }
        Data item_data;
    };
    // Creates new list
    List() {
        this->head = nullptr;
        this->size = 0;
    }

    Data operator[](int index) {
        if (index == -1) throw "Element was not found!\n";
        else {
            int counter = 0;
            Item* current = this->head;
            while (current != nullptr) {
                Data data = current->data();
                if (index == size) return data;
                else if (counter > size) throw "Index out of range exception!\n";
                else {
                    if (counter == index) return data;
                    current = current->next();
                    counter++;
                }
            }
        }
    }
    // Destroys the list and frees the memory
    ~List() {
        Item* toDelete = this->head;
        while (toDelete) {
            this->head = toDelete->next_item;
            delete toDelete;
            toDelete = this->head;
        }
    }
    void list_delete(List<Data>* list) {
        Item* toDelete = list->head;
        while (toDelete) {
            list->head= toDelete->next();
            delete toDelete;
            toDelete = list->head;
        }
    }

    // Retrieves the first item from the list
    Item* first() {
        if (list_empty()) return nullptr;//throw "List is empty\n";
        else return this->head;
    }


    Item* push_back(Data data) {
        this->size++;
        if (list_empty()) {
            return this->head = new Item(data, nullptr);
        }
        else {
            Item* current = this->head;
            while (current->next() != nullptr) {
                current = current->next();
            }
            return current->next_item = new Item(data, nullptr);
        }
    }

    // Inserts new list item into the beginning
    Item* insert(Data data) {
        this->size++;
        if (this->head == nullptr) return this->head = new Item(data, nullptr);
        else return this->head = new Item(data, this->head);
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data) {
        this->size++;
        if (this->head == nullptr) return this->head = new Item(data, nullptr);
        else return item->next_item = new Item(data, item->next_item);
    }

    // Deletes the specified list item.
    // Returns pointer to the item next to the deleted one.
    // Not applicable for the singly linked lists.
    // Should be O(1)
    Item* erase(Item* item) {
        this->size--;
        if (list_empty()) throw "List is empty\n\n";
        else if (item == this->head) {
            Item* toDelete = this->head;
            this->head = toDelete->next();
            delete toDelete;
            return this->head->next();
        }
        else {
            Item* previous = this->head;
            
            while (previous->next() != item) {
                previous = previous->next();
            }
            Item* toDelete = previous->next();
            if (previous->next_item) previous->next_item = toDelete->next_item;
            delete toDelete;
            return previous->next_item;
        }
    }

    Item* erase(int index) {
        this->size--;
        if (list_empty()) throw "List is empty\n\n";
        else if (index == 0) {
            Item* toDelete = this->head;
            this->head = toDelete->next();
            delete toDelete;
            return this->head->next();
        }
        else {
            Item* previous = this->head;
            for (size_t i = 0; i < index - 1; i++) {
                previous = previous->next();
            }
            Item* toDelete = previous->next();
            if (previous->next()) previous->next_item = toDelete->next();
            delete toDelete;
            return previous->next();
        }
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item* erase_next(Item* item) {
        if (item->next()) {
            this->size--;
            Item* next_before_delete = item->next_item->next_item;
            delete item->next_item;
            item->next_item = next_before_delete;
            return next_before_delete;
        }
        else {
            throw "Nullptr exception!";
        }
        return 0;
    }
    //checking for an empty list
    bool list_empty() { return (this->head == nullptr) ? true : false; }
    
    size_t getSize() { return this->size; }
private:
    Item* head;
    size_t size;
};

#endif
