#ifndef LIBRARY_CPP_TEMPLATE_LIST_H
#define LIBRARY_CPP_TEMPLATE_LIST_H

#include <cstddef>

namespace graph {

template <typename T>
class List {
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
    };

public:
    class iterator {
        friend class List;
    public:
        iterator() : node_(nullptr) {}
        explicit iterator(Node* n) : node_(n) {}
        T& operator*() const { return node_->value; }
        T* operator->() const { return &node_->value; }
        iterator& operator++() { node_ = node_->next; return *this; }
        bool operator!=(const iterator& o) const { return node_ != o.node_; }
        bool operator==(const iterator& o) const { return node_ == o.node_; }
    private:
        Node* node_;
    };

    class const_iterator {
        friend class List;
    public:
        const_iterator() : node_(nullptr) {}
        explicit const_iterator(const Node* n) : node_(n) {}
        const T& operator*() const { return node_->value; }
        const T* operator->() const { return &node_->value; }
        const_iterator& operator++() { node_ = node_->next; return *this; }
        bool operator!=(const const_iterator& o) const { return node_ != o.node_; }
        bool operator==(const const_iterator& o) const { return node_ == o.node_; }
    private:
        const Node* node_;
    };

    List() : head_(nullptr), tail_(nullptr), size_(0) {}

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (const_iterator it = other.begin(); it != other.end(); ++it) {
            push_back(*it);
        }
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (const_iterator it = other.begin(); it != other.end(); ++it) {
                push_back(*it);
            }
        }
        return *this;
    }

    ~List() { clear(); }

    void clear() {
        Node* cur = head_;
        while (cur) {
            Node* n = cur->next;
            delete cur;
            cur = n;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    void push_back(const T& v) {
        Node* n = new Node(v);
        if (!tail_) {
            head_ = tail_ = n;
        } else {
            tail_->next = n;
            n->prev = tail_;
            tail_ = n;
        }
        ++size_;
    }

    iterator erase(iterator pos) {
        Node* n = pos.node_;
        if (!n) return end();
        Node* nxt = n->next;
        if (n->prev) n->prev->next = n->next; else head_ = n->next;
        if (n->next) n->next->prev = n->prev; else tail_ = n->prev;
        delete n;
        --size_;
        return iterator(nxt);
    }

    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(nullptr); }
    const_iterator begin() const { return const_iterator(head_); }
    const_iterator end() const { return const_iterator(nullptr); }

private:
    Node* head_;
    Node* tail_;
    std::size_t size_;
};

}

#endif
