#ifndef SPLAY_MAP_H
#define SPLAY_MAP_H

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "associative_array.h"

template <typename Key, typename Value>
class SplayMap : public AssociativeArray<Key, Value> {
    using Base = AssociativeArray<Key, Value>;
    using typename Base::Order;

    struct Node {
        Key key;
        Value value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        Node(const Key& k, const Value& v) : key(k), value(v) {}
    };

    Node* root_ = nullptr;
    std::size_t size_ = 0;

    void rotate(Node* x) {
        Node* p = x->parent;
        Node* g = p->parent;
        if (p->left == x) {
            p->left = x->right;
            if (x->right) x->right->parent = p;
            x->right = p;
        } else {
            p->right = x->left;
            if (x->left) x->left->parent = p;
            x->left = p;
        }
        p->parent = x;
        x->parent = g;
        if (g) {
            if (g->left == p) g->left = x;
            else g->right = x;
        }
    }

    void splay(Node* x) {
        if (!x) return;
        while (x->parent) {
            Node* p = x->parent;
            Node* g = p->parent;
            if (!g) {
                rotate(x);
            } else if ((g->left == p) == (p->left == x)) {
                rotate(p); rotate(x);
            } else {
                rotate(x); rotate(x);
            }
        }
        root_ = x;
    }

    Node* findLast(const Key& key, Node* start = nullptr) const {
        Node* cur = start ? start : root_;
        Node* last = nullptr;
        while (cur) {
            last = cur;
            if (key < cur->key) cur = cur->left;
            else if (cur->key < key) cur = cur->right;
            else break;
        }
        return last;
    }

    void destroyTree(Node* root) {
        if (!root) return;
        std::vector<Node*> nodes;
        nodes.push_back(root);

        while (!nodes.empty()) {
            Node* current = nodes.back();
            nodes.pop_back();

            if (current->left) nodes.push_back(current->left);
            if (current->right) nodes.push_back(current->right);

            delete current;
        }
    }

public:
    SplayMap() = default;
    SplayMap(const SplayMap&) = delete;
    SplayMap& operator=(const SplayMap&) = delete;
    ~SplayMap() override { clear(); }

    bool insert(const Key& key, const Value& value) override {
        if (!root_) {
            root_ = new Node(key, value);
            size_++;
            return true;
        }
        Node* n = findLast(key);
        splay(n);
        if (root_->key == key) {
            root_->value = value;
            return false;
        }
        Node* newRoot = new Node(key, value);
        if (key < root_->key) {
            newRoot->left = root_->left;
            newRoot->right = root_;
            root_->left = nullptr;
            if (newRoot->left) newRoot->left->parent = newRoot;
        } else {
            newRoot->right = root_->right;
            newRoot->left = root_;
            root_->right = nullptr;
            if (newRoot->right) newRoot->right->parent = newRoot;
        }
        root_->parent = newRoot;
        root_ = newRoot;
        size_++;
        return true;
    }

    Value* find(const Key& key) override {
        if (!root_) return nullptr;
        splay(findLast(key));
        if (root_->key == key) return &root_->value;
        return nullptr;
    }

    const Value* find(const Key& key) const override {
        return const_cast<SplayMap*>(this)->find(key);
    }

    bool erase(const Key& key) override {
        if (!root_) return false;
        splay(findLast(key));
        if (root_->key != key) return false;

        Node* oldRoot = root_;
        if (!root_->left) {
            root_ = root_->right;
            if (root_) root_->parent = nullptr;
        } else {
            Node* leftSub = root_->left;
            leftSub->parent = nullptr;
            splay(findLast(key, leftSub));
            root_->right = oldRoot->right;
            if (root_->right) root_->right->parent = root_;
        }
        delete oldRoot;
        size_--;
        return true;
    }

    bool contains(const Key& key) const override { return find(key) != nullptr; }
    std::size_t size() const override { return size_; }
    bool empty() const override { return size_ == 0; }

    void clear() override {
        destroyTree(root_);
        root_ = nullptr;
        size_ = 0;
    }

    class SplayIterator : public Base::Iterator {
        const SplayMap* map_;
        Node* current_;
        Order order_;

        Node* minNode(Node* n) const {
            while (n && n->left) n = n->left;
            return n;
        }
        Node* maxNode(Node* n) const {
            while (n && n->right) n = n->right;
            return n;
        }
        Node* nextNode(Node* n) const {
            if (!n) return nullptr;
            if (order_ == Order::Ascending) {
                if (n->right) return minNode(n->right);
                while (n->parent && n->parent->right == n) n = n->parent;
                return n->parent;
            } else {
                if (n->left) return maxNode(n->left);
                while (n->parent && n->parent->left == n) n = n->parent;
                return n->parent;
            }
        }

    public:
        SplayIterator(const SplayMap* map, Order order) : map_(map), order_(order) {
            current_ = (order_ == Order::Ascending) ? minNode(map->root_) : maxNode(map->root_);
        }

        bool valid() const override { return current_ != nullptr; }
        void next() override { current_ = nextNode(current_); }
        const Key& key() const override { return current_->key; }
        const Value& value() const override { return current_->value; }
    };

    std::unique_ptr<typename Base::Iterator> createIterator(Order order = Order::Ascending) const override {
        return std::make_unique<SplayIterator>(this, order);
    }
};

#endif