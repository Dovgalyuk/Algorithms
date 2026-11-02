#ifndef RB_TREE_H
#define RB_TREE_H

#include <cstddef>
#include <stdexcept>
#include <utility>

enum class Color { RED, BLACK };

template <typename Key, typename Value>
class RBTree {
public:
    struct Node {
        Key key;
        Value value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Key& k, const Value& v, Color c = Color::RED)
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(nullptr) {
        }
    };

private:
    Node* root;
    size_t size_;

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* minimum(Node* node) const {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;

        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;

        if (y->parent == nullptr) {
            root = x;
        }
        else if (y == y->parent->left) {
            y->parent->left = x;
        }
        else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node* z) {
        while (z->parent != nullptr && z->parent->color == Color::RED) {
            if (z->parent == z->parent->parent->left) {
                Node* uncle = z->parent->parent->right;

                if (uncle != nullptr && uncle->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotateLeft(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotateRight(z->parent->parent);
                }
            }
            else {
                Node* uncle = z->parent->parent->left;

                if (uncle != nullptr && uncle->color == Color::RED) {
                    z->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = Color::BLACK;
    }

    Node* maximum(Node* node) const {
        while (node && node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void fixDelete(Node* x, Node* parent) {
        while (x != root && (x == nullptr || x->color == Color::BLACK)) {
            if (x == parent->left) {
                Node* w = parent->right;
                if (w == nullptr) break;

                if (w->color == Color::RED) {
                    w->color = Color::BLACK;
                    parent->color = Color::RED;
                    rotateLeft(parent);
                    w = parent->right;
                }
                if ((w->left == nullptr || w->left->color == Color::BLACK) &&
                    (w->right == nullptr || w->right->color == Color::BLACK)) {
                    w->color = Color::RED;
                    x = parent;
                    parent = x->parent;
                }
                else {
                    if (w->right == nullptr || w->right->color == Color::BLACK) {
                        if (w->left != nullptr) w->left->color = Color::BLACK;
                        w->color = Color::RED;
                        rotateRight(w);
                        w = parent->right;
                    }
                    w->color = parent->color;
                    parent->color = Color::BLACK;
                    if (w->right != nullptr) w->right->color = Color::BLACK;
                    rotateLeft(parent);
                    x = root;
                }
            }
            else {
                Node* w = parent->left;
                if (w == nullptr) break;

                if (w->color == Color::RED) {
                    w->color = Color::BLACK;
                    parent->color = Color::RED;
                    rotateRight(parent);
                    w = parent->left;
                }
                if ((w->right == nullptr || w->right->color == Color::BLACK) &&
                    (w->left == nullptr || w->left->color == Color::BLACK)) {
                    w->color = Color::RED;
                    x = parent;
                    parent = x->parent;
                }
                else {
                    if (w->left == nullptr || w->left->color == Color::BLACK) {
                        if (w->right != nullptr) w->right->color = Color::BLACK;
                        w->color = Color::RED;
                        rotateLeft(w);
                        w = parent->left;
                    }
                    w->color = parent->color;
                    parent->color = Color::BLACK;
                    if (w->left != nullptr) w->left->color = Color::BLACK;
                    rotateRight(parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->color = Color::BLACK;
    }

public:
    RBTree() : root(nullptr), size_(0) {}
    ~RBTree() { clear(root); }

    size_t size() const { return size_; }

    void insert(const Key& key, const Value& value) {
        Node* z = new Node(key, value);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            }
            else if (z->key > x->key) {
                x = x->right;
            }
            else {
                x->value = value;
                delete z;
                return;
            }
        }

        z->parent = y;
        if (y == nullptr) {
            root = z;
        }
        else if (z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
        size_++;
        fixInsert(z);
    }

    Node* find(const Key& key) const {
        Node* current = root;
        while (current != nullptr) {
            if (key == current->key) return current;
            else if (key < current->key) current = current->left;
            else current = current->right;
        }
        return nullptr;
    }

    void remove(const Key& key) {
        Node* z = find(key);
        if (z == nullptr) return;

        Node* y = z;
        Node* x = nullptr;
        Node* x_parent = nullptr;
        Color y_original_color = y->color;

        if (z->left == nullptr) {
            x = z->right;
            x_parent = z->parent;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            x_parent = z->parent;
            transplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;

            if (y->parent == z) {
                x_parent = y;
                if (x != nullptr) x->parent = y;
            }
            else {
                x_parent = y->parent;
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;
        size_--;

        if (y_original_color == Color::BLACK) {
            fixDelete(x, x_parent);
        }
    }

    int getHeight() const {
        return getHeightHelper(root);
    }
    int getHeightHelper(Node* node) const {
        if (!node) return 0;
        int leftH = getHeightHelper(node->left);
        int rightH = getHeightHelper(node->right);
        return (leftH > rightH ? leftH : rightH) + 1;
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        bool operator!=(const Iterator& other) const { return current != other.current; }
        bool operator==(const Iterator& other) const { return current == other.current; }

        Iterator& operator++() {
            if (current->right != nullptr) {
                current = current->right;
                while (current->left != nullptr) {
                    current = current->left;
                }
            }
            else {
                Node* parent = current->parent;
                while (parent != nullptr && current == parent->right) {
                    current = parent;
                    parent = parent->parent;
                }
                current = parent;
            }
            return *this;
        }

        std::pair<const Key&, Value&> operator*() const {
            return { current->key, current->value };
        }
    };

    Iterator begin() const { return Iterator(minimum(root)); }
    Iterator end() const { return Iterator(nullptr); }
};
#endif