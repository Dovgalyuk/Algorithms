#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

#include <cstddef>  // для nullptr

template <typename Data>
class List {
public:
    class Item {
    public:
        Item(Data data, Item* next = nullptr)
            : _data(data), _next(next) {}

        Item* next() { return _next; }
        Data data() const { return _data; }

        void set_next(Item* next) { _next = next; }

    private:
        Data _data;
        Item* _next;

        friend class List<Data>;
    };

    // Конструктор
    List() : _head(nullptr) {}

    // Конструктор копирования
    List(const List& other) : _head(nullptr) {
        Item* current = other._head;
        Item** tail = &_head;

        while (current) {
            *tail = new Item(current->data());
            tail = &((*tail)->_next);
            current = current->_next;
        }
    }

    // Оператор присваивания
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Item* current = other._head;
            Item** tail = &_head;

            while (current) {
                *tail = new Item(current->data());
                tail = &((*tail)->_next);
                current = current->_next;
            }
        }
        return *this;
    }

    // Деструктор
    ~List() {
        clear();
    }

    // Вернуть первый элемент
    Item* first() {
        return _head;
    }

    // Вставить элемент в начало
    Item* insert(Data data) {
        _head = new Item(data, _head);
        return _head;
    }

    // Вставить после указанного элемента
    Item* insert_after(Item* item, Data data) {
        if (!item) return insert(data);
        Item* new_item = new Item(data, item->_next);
        item->_next = new_item;
        return new_item;
    }

    // Удалить первый элемент
    Item* erase_first() {
        if (!_head) return nullptr;
        Item* temp = _head;
        _head = _head->_next;
        delete temp;
        return _head;
    }

    // Удалить следующий элемент
    Item* erase_next(Item* item) {
        if (!item) return erase_first();
        if (!item->_next) return nullptr;
        Item* temp = item->_next;
        item->_next = temp->_next;
        delete temp;
        return item->_next;
    }

private:
    Item* _head;

    void clear() {
        while (_head) {
            erase_first();
        }
    }
};

#endif
