#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H
template <typename Data>
class AssociativeArray {
    class Node {
    public:
        int key;
        Node* parent = nullptr;
        Node* right = nullptr;
        Node* left = nullptr;
        Data data;

        Node(int key, Data data): key(key), data(data) {}

        void setChild() {
            if (right) {
                right->parent = this;
            }
            if (left) {
                left->parent = this;
            }
        }

        void rotate() {
            if (!parent) {
                return;
            }

            Node* grandParent = parent->parent;
            if (grandParent) {
                if (grandParent->left == parent) {
                    grandParent->left = this;
                } else {
                    grandParent->right = this;
                }
            }

            if (parent->left == this) {
                parent->left = right;
                right = parent;
            } else {
                parent->right = left;
                left = parent;
            }

            setChild();
            parent->setChild();
            parent = grandParent;
        }

        void splay() {
            if (!parent) {
                return;
            }
            if (!parent->parent) {
                rotate();
            } else {
                if ((parent->parent->left == parent) == (parent->left == this)) {
                    parent->parent->rotate();
                    rotate();
                } else {
                    rotate();
                    rotate();
                }
            }
        }

        Node* findNearest(int requiredKey) {
            Node* cur = this;
            while (cur->key != requiredKey) {
                Node* last = cur;
                if (requiredKey < cur->key) {
                    cur = cur->left;
                } else {
                    cur = cur->right;
                }
                if (cur) {
                    cur->splay();
                } else {
                    return last;
                }
            }
            return cur;
        }

    };

public:
    ~AssociativeArray() {
        while (root) {
            remove(root->key);
        }
    }

    Data find(int key) {
        Node* founded = findNode(key);
        return (founded && founded->key == key) ? founded->data : NULL;
    }

    void insert(int key, Data data) {
        Node* newRoot;
        Node* itOrChild = (root) ? root->findNearest(key) : nullptr;
        if (itOrChild && itOrChild->key == key) {
            newRoot = itOrChild;
            newRoot->data = data;
        } else {
            newRoot = new Node(key, data);
            if (itOrChild) {
                itOrChild->parent = newRoot;
                if (itOrChild->key < key) {
                    newRoot->left = itOrChild;
                } else {
                    newRoot->right = itOrChild;
                }
            }
        }
        amountNodes++;
        root = newRoot;
    }

    void remove(int key) {
        Node* newRoot = nullptr;
        Node* node = findNode(key);
        if (!node) {
            return;
        }
        if (!node->left) {
            newRoot = node->right;
        } else if (!node->right) {
            newRoot = node->left;
        } else if (!node->right && !node->left) {
            newRoot = node->right->findNearest(node->left->key);
            newRoot->left = node->left;
            newRoot->left->parent = newRoot;
            newRoot->parent = nullptr;
        }
        delete node;
        amountNodes--;
        root = newRoot;
    }

private:
    Node* findNode(int key) {
        if (!root) {
            return nullptr;
        }
        Node* founded = root->findNearest(key);
        root = founded;
        return (founded && founded->key == key) ? founded : nullptr;
    }

protected:
    Node* root = nullptr;
    int amountNodes = 0;

};
#endif
