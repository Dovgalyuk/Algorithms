#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include <cstddef>  // для nullptr
#include <stdexcept>  // для std::out_of_range

template <typename Data>
class Queue {
public:
    Queue() : _head(nullptr), _tail(nullptr) {}

    Queue(const Queue &other) : _head(nullptr), _tail(nullptr) {
        Node* current = other._head;
        while (current) {
            insert(current->data);
            current = current->next;
        }
    }

    Queue &operator=(const Queue &other) {
        if (this != &other) {
            clear();
            Node* current = other._head;
            while (current) {
                insert(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    ~Queue() {
        clear();
    }

    void insert(Data data) {
        Node* new_node = new Node(data);
        if (!_tail) {
            _head = _tail = new_node;
        } else {
            _tail->next = new_node;
            _tail = new_node;
        }
    }

    Data get() const {
        if (!_head) throw std::out_of_range("Queue is empty");
        return _head->data;
    }

    void remove() {
        if (!_head) return;
        Node* temp = _head;
        _head = _head->next;
        delete temp;
        if (!_head) _tail = nullptr;
    }

    bool empty() const {
        return _head == nullptr;
    }

private:
    struct Node {
        Data data;
        Node* next;
        Node(Data d) : data(d), next(nullptr) {}
    };

    Node* _head;
    Node* _tail;

    void clear() {
        while (_head) {
            remove();
        }
    }
};

#endif
