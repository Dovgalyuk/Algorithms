#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data>
class List {
public:
    class Item
    {
    public:
        Data data() const { return data_value; } 
        Item *next() { return next_item; }
        Item* prev() { return prev_item; }

        Item(Data data) : data_value(data), next_item(nullptr), prev_item(nullptr) {} 

    private:
        // internal data here
        Data data_value;
        Item* next_item;
        Item* prev_item;

        friend class List <Data>;
    };

    // Creates new list
    List() : first_item(nullptr) {}
    
    // copy constructor
    List(const List& a) : first_item(nullptr) {
        Item* current = a.first_item;
        while (current != nullptr) {
            insert(current->data());
            current = current->next();
        }
    }
   
    // assignment operator
    List& operator=(const List& a) {
        if (this != &a) {
            while (first_item) {
                erase_first();
            }
            Item* current = a.first_item;
            while (current != nullptr) {
                insert(current->data());
                current = current->next();
            }
        }
        return *this;
    }

    // Destroys the list and frees the memory
    ~List() {
        while (first_item != nullptr) {
            erase_first();
        }
    }
    
    // Retrieves the first item from the list
    Item* first() {
        return first_item;
    }
    
    // Inserts new list item into the beginning
    Item* insert(Data data) {
        Item* new_item = new Item(data);
        new_item->next_item = first_item;

        if (first_item != nullptr) {
            first_item->prev_item = new_item;
        }

        first_item = new_item;

        return new_item;
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data) {
        if (!item) {
            return nullptr;
        }

        Item* new_item = new Item(data);

        new_item->next_item = item->next_item;
        new_item->prev_item = item;

        if (item->next_item != nullptr) {
            item->next_item->prev_item = new_item;
        }

        item->next_item = new_item;

        return new_item;
    }
    
    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item* erase_first() {
        if (first_item == nullptr) {
            return nullptr;
        }

        Item* current_item = first_item->next_item;

        if (current_item != nullptr) {
            current_item->prev_item = nullptr;
            delete first_item;
            first_item = current_item;
        }
        else {
            delete first_item;
            first_item = nullptr;
        }

        return first_item;
    }
    
    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item* erase_next(Item* item) {
        if (!item || !item->next_item) {
            return nullptr;
        }
        Item* current_item = item->next_item->next_item;
        delete item->next_item;
        item->next_item = current_item;
        if (current_item != nullptr) {
            current_item->prev_item = item;
        }
        return current_item;
    }
    
private:
    // private data should be here
    Item* first_item;
};

#endif