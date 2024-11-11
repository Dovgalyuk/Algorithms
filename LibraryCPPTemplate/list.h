#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List
{
public:
    class Item
    {
    public:
        Item(Data data) : _data(data), _next(this), _prev(this) {}

        Item* next() { return _next; }
        Item* prev() { return _prev; }
        Data data() const { return _data; }
    private:
        // internal data here
        Data _data;
        Item* _next;
        Item* _prev;

        friend class List; // Allow the List class to access private data
    };

    // Creates new list
    List() : _head(nullptr)
    {
    }

    // copy constructor
    List(const List& a) : _head(nullptr) {
        if (a._head) {
            Item* current = a.first()->prev();

            do {
                // copy in reverse order to save the original order
                insert(current->data());
                current = current->prev();
            } while (current != a.first()->prev());
        }
    }

    // assignment operator
    List& operator=(const List& a) {
        if (this != &a) {
            this->~List(); // Destroy the current list

            // Create a new list based on "a" in the memory area that has already been allocated for the current object
            new (this) List(a);
        }

        return *this;
    }

    // Destroys the list and frees the memory
    ~List()
    {
        while (_head) {
            erase_first();
        }
    }

    // Retrieves the first item from the list
    Item* first() const
    {
        return _head;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data)
    {
        Item* new_item = new Item(data);

        if (_head) {
            new_item->_next = _head; // The new item points to the old head
            new_item->_prev = _head->_prev; // The new item points to the last item
            _head->_prev->_next = new_item;   // The last item points to the new head
            _head->_prev = new_item;  // The old head points to the new item
        }
        else {
            new_item->_next = new_item; //  Pointing to himself
            new_item->_prev = new_item; //  Pointing to himself
        }

        _head = new_item;

        return new_item;
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data)
    {
        if (!item) return nullptr;

        Item* new_item = new Item(data);

        new_item->_next = item->_next;
        new_item->_prev = item;
        item->_next->_prev = new_item;
        item->_next = new_item;

        return new_item;
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item* erase_first()
    {
        if (!_head) return nullptr;

        Item* to_delete = _head;
        if (_head->_next == _head) { // Only one item in the list
            _head = nullptr;
        }
        else {
            _head->_prev->_next = _head->_next;
            _head->_next->_prev = _head->_prev;
            _head = _head->_next;
        }

        delete to_delete;
        return _head;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item* erase_next(Item* item)
    {
        if (!item || item->_next == item) return nullptr; // No next item or only one item

        Item* to_delete = item->_next;
        item->_next = to_delete->_next;
        to_delete->_next->_prev = item;

        delete to_delete;
        return item->next();
    }
private:
    // private data should be here
    Item* _head; // Pointer to the first item in the list
};
#endif