#ifndef LIST_H
#define LIST_H

#include <cstddef>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;
};

template <typename T>
class List {
public:
    class Iterator {
    public:
        Iterator(Node<T>* n) : current(n) {}

        Node<T>* operator->() { return current; }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    private:
        Node<T>* current;
    };

    List() {
        dummy = new Node<T>();
        dummy->next = dummy;
        dummy->prev = dummy;
    }

    ~List() {
        Node<T>* cur = dummy->next;
        while (cur != dummy) {
            Node<T>* next = cur->next;
            delete cur;
            cur = next;
        }
        delete dummy;
    }

    void push_back(const T& val) {
        Node<T>* n = new Node<T>{ val, dummy, dummy->prev };
        dummy->prev->next = n;
        dummy->prev = n;
    }

    Iterator begin() { return Iterator(dummy->next); }
    Iterator end() { return Iterator(dummy); }

private:
    Node<T>* dummy;
};

#endif