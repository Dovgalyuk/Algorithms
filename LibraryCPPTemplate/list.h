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
    List() : _head(nullptr), _tail(nullptr)
    {
    }

    // copy constructor
    List(const List& a) : _head(nullptr), _tail(nullptr) {
        if (a._head) {
            Item* current = a._tail;

            do {
                // copy in reverse order to save the original order
                insert(current->data());
                current = current->prev();
            } while (current != a._tail);
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

    Item* last() const
    {
        return _tail;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data)
    {
        Item* new_item = new Item(data);

        if (_head) {
            new_item->_next = _head; // Новый элемент указывает на старую голову
            new_item->_prev = _tail; // Новый элемент указывает на старый хвост
            _head->_prev = new_item;  // Старая голова теперь указывает на новый элемент 
            _tail->_next = new_item;   // Старый хвост теперь указывает на новый элемент 
        }
        else {
            new_item->_next = new_item; // Указываем на себя
            new_item->_prev = new_item; // Указываем на себя
            _tail = new_item;           // Устанавливаем хвост
        }

        _head = new_item;

        return new_item;
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data)
    {
        if (!item) return nullptr;

        Item* new_item = new Item(data);

        if (_head) {
            new_item->_next = item->_next;
            new_item->_prev = item;
            item->_next->_prev = new_item;
            item->_next = new_item;

            if (item == _tail) _tail = new_item;
        }

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
            _tail = nullptr;
        }
        else {
            _head = _head->_next;
            _tail->_next = _head;
            _head->_prev = _tail;
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

        if (item->next == _tail) _tail = item;

        Item* to_delete = item->next();
        item->next_ = to_delete->next();

        delete to_delete;
        return item->next();
    }
private:
    // private data should be here
    Item* _head; // Pointer to the first item in the list
    Item* _tail;
};
#endif
